#ifndef ast_eval_hpp
#define ast_eval_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class Eval
    : public Base
{
private:
    BasePtr var;
    BasePtr val;
public:
   
    Eval(BasePtr _var, BasePtr _val)
        : var(_var)
        , val(_val)

    {}
 

    virtual ~Eval()
    {
        delete var;
        delete val;
    }

    BasePtr getVar() const
    { return var; }

    BasePtr getVal() const
    { return val; }

    virtual void countEvals(std::vector<BasePtr> *currentList) const override
    {  
        currentList->push_back(this);
    }


    virtual void print(std::ostream &dst) const override
    {
        var->print(dst);
        dst << " = ";
        val->print(dst);
    }
     virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        // What is the value of the right hand side of the assign 
        val->compile(rn("t0"), dst, mainContext);
        dst<< SW(rn("t0"), std::to_string(findVar(var->getId(),mainContext)), rn("sp")) << std::endl;
        // Store t0 in the location of variable X
    }
};

#endif
