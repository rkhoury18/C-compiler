#ifndef ast_declare_hpp
#define ast_declare_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class Declare
    : public Base
{
private:
    BasePtr var;
    BasePtr val;

public:

    Declare(BasePtr _var, BasePtr _val)
        : var(_var)
        , val(_val)
        
    {}
   

    virtual ~Declare()
    {
        delete var;
        delete val;
    }

    BasePtr getVar() const
    { return var; }

    BasePtr getVal() const
    { return val; }

    virtual int countDeclares() const override{
        return 1;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << "int ";
        var->print(dst);
        dst << " = ";
        val->print(dst);
    }
    
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        // Whenever you enter a new scope do stackScope.push_back(*(new std::vector<std::pair<std::string, int>>))
        // This should create a new 'Scope' to add variables on to.

        // If you leave a scope, do stackScope.pop_back();

        val->compile(rn("t0"), dst, mainContext); // Evaluate assigned value
        dst << SW(rn("t0"), std::to_string(mainContext->offset), rn("sp"))<<std::endl; // Store the variable

        std::pair<std::string, int> newVar = std::make_pair(var->getId(), mainContext->offset); // Create a pair with the variable name and offset
        
        // Add to most current scope.
        mainContext->stackScope.back().push_back( std::make_pair(var->getId(), mainContext->offset) ); // 

        mainContext->offset+=4; // Make next variable be written to a new location in the stack
        
        // Create a Variable.
    }
};

#endif
