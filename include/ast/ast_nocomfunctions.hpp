#ifndef ast_nocomfunctions_hpp
#define ast_nocomfunctions_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class NoComFunctions
    : public Base
{
private:
    BasePtr var;
    BasePtr arg;
protected:
    std::string type;
    NoComFunctions(BasePtr _var, BasePtr _arg,std::string _type)
        : var(_var)
        , arg(_arg)
        , type(_type)

        
    {}
public:

    virtual ~NoComFunctions()
    {
        delete var;
        delete arg;
   
    }

    BasePtr getvar() const
    { return var; }

    BasePtr getArg() const
    { return arg; }

    std::string getType() const
    { return type;}

    


    virtual void print(std::ostream &dst) const override
    {
        dst<<type<<" ";
        var->print(dst);
        dst<<" ( ";
        if (arg != NULL ){
            arg->print(dst);
        }
        dst << " ) ; \n";
       
    
    }
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {

    }
};
class NOCOMVoidEmptyFunction
    : public NoComFunctions
{
public:
    NOCOMVoidEmptyFunction(BasePtr _var)
        : NoComFunctions(_var, NULL, "Void")
    {}
};

class NOCOMVoidEmptyFunctionArgs
    : public NoComFunctions
{
public:
    NOCOMVoidEmptyFunctionArgs(BasePtr _var, BasePtr _arg)
        : NoComFunctions(_var, _arg, "Void")
    {}
};

class NOCOMIntEmptyArgFunction
    : public NoComFunctions
{
public:
    NOCOMIntEmptyArgFunction(BasePtr _var)
        : NoComFunctions(_var, NULL, "Int")
    {}
};

class NOCOMIntEmptyFunction
    : public NoComFunctions
{
public:
    NOCOMIntEmptyFunction(BasePtr _var, BasePtr _arg)
        : NoComFunctions(_var, _arg, "Int")
    {}
};


#endif
