#ifndef ast_increment_hpp
#define ast_increment_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class Increment
    : public Base
{
private:
    BasePtr var;
protected:
    std::string type;
    Increment(BasePtr _var,std::string _type)
        : var(_var)
        , type(_type)
       
    {}
public:
   
    virtual ~Increment()
    {
        delete var;
    }

    BasePtr getvar() const
    { return var; }


    virtual void print(std::ostream &dst) const override
    {
        var->print(dst);
        if (type=="Inc"){
            dst<< " ++ ";
        }
        if (type=="Dec"){
            dst<<" -- ";
        }
 
    }
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        if(type=="Dec"){
                // What is the value of the right hand side of the assign 
        
            var->compile(rn("t0"), dst, mainContext);

            dst<<ADDIU(rn("t1"), rn("t0"), "1")<<std::endl;
            dst<< SW(rn("t1"), std::to_string(findVar(var->getId(),mainContext)), rn("sp")) << std::endl;
        }

            

    }
};

class Inc
    : public Increment
{
public:

    Inc(BasePtr _var)
        : Increment(_var,"Inc")
    {}


};

class Dec
    : public Increment
{
public:
    
    Dec(BasePtr _var)
        : Increment(_var,"Dec")
    {}



};

#endif