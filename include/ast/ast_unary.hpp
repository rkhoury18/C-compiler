#ifndef ast_unary_hpp
#define ast_unary_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class Unary
    : public Base
{
private:
    BasePtr base;
protected:
    std::string type;
    Unary(const BasePtr _base,std::string _type)
        : base(_base)
        , type(_type)
       
    {}
public:
   
    virtual ~Unary()
    {
        delete base;
    }

    virtual const char *getOpcode() const =0;

    BasePtr getBase() const
    { return base; }

    virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << getOpcode();
        dst << " ";
        base->print(dst);
        dst << " )";
    }
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        if (type=="Neg"){
            base->compile(rn("t0"),dst,mainContext);
            dst<<SUB(destReg, rn("zero"), rn("t0"))<<std::endl;
            
        }
        else if (type=="Not"){
            base->compile(rn("t0"),dst,mainContext);
            dst<<SLTU(rn("t0"), rn("zero"), rn("t0"))<<std::endl;
        }
        else if (type=="BitNot"){
            base->compile(rn("t0"),dst,mainContext);

            // Can be done using a NOR

            dst<<NOR(destReg, rn("t0"), rn("zero"))<<std::endl;
            
        }
    }
};

class NegOperator
    : public Unary
{
public:

    NegOperator(const BasePtr _expr)
        : Unary(_expr,"Neg")
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

};

class NotOperator
    : public Unary
{
public:
    
    NotOperator(const BasePtr _expr)
        : Unary(_expr,"Not")
    {}

    virtual const char *getOpcode() const override
    { return "!"; }

};

class BitNotOperator
    : public Unary
{
public:
    BitNotOperator(const BasePtr _expr)
        : Unary(_expr,"BitNot")
    {}

    virtual const char *getOpcode() const override
    { return "~"; }

};

#endif
