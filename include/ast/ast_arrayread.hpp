#ifndef ast_arrayread_hpp
#define ast_arrayread_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class ArrayRead
    : public Base
{
private:
    BasePtr var;
    int index;

public:

    ArrayRead(BasePtr _var,int _index)
        : var(_var)
        , index(_index)
        
    {}
   

    virtual ~ArrayRead()
    {
        delete var;
        
    }

    BasePtr getVar() const
    { return var; }

    int getIndex() const
    { return index; }



    virtual void print(std::ostream &dst) const override
    {
        dst << "int ";
        var->print(dst);
        dst << " [ "<<index;
        dst<< " ] ";

    }
    
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        // What is the value of the right hand side of the assign 
        dst<< LW(destReg, std::to_string(findVar((var->getId())+"["+std::to_string(index)+"]",mainContext)), rn("sp")) << std::endl;
        // Store t0 in the location of variable X


    }
};

class ArRead
    : public ArrayRead
{
public:
    ArRead(BasePtr _var, int _index )
        : ArrayRead(_var, _index)
    {}
};



#endif