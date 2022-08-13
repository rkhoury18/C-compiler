#ifndef ast_arraywrite_hpp
#define ast_arraywrite_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class ArrayWrite
    : public Base
{
private:
    BasePtr var;
    int index;
    BasePtr val;

public:

    ArrayWrite(BasePtr _var,int _index, BasePtr _val)
        : var(_var)
        , index(_index)
        , val(_val)
        
    {}
   

    virtual ~ArrayWrite()
    {
        delete var;
        delete val;
        
    }

    BasePtr getVar() const
    { return var; }

    int getIndex() const
    { return index; }

    BasePtr getVal() const
    { return val; }

    virtual void print(std::ostream &dst) const override
    {
        dst << "int ";
        var->print(dst);
        dst << " [ "<<index;
        dst<< " ] ";
        dst <<" = ";
        val->print(dst);

    }
    
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        // What is the value of the right hand side of the assign 
        val->compile(rn("t0"), dst, mainContext); 
        dst<< SW(rn("t0"), std::to_string(findVar((var->getId())+"["+std::to_string(index)+"]",mainContext)), rn("sp")) << std::endl;
        // Store t0 in the location of variable X
        

    }
};

class ArWrite
    : public ArrayWrite
{
public:
    ArWrite(BasePtr _var, int _index, BasePtr _val )
        : ArrayWrite(_var, _index, _val)
    {}
};



#endif