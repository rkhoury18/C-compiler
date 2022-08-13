#ifndef ast_functioncall_hpp
#define ast_functioncall_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class FunctionCall
    : public Base
{
private:

    std::string name;
    BasePtr par;

public:

    FunctionCall(std::string _name, BasePtr _par )
        : name(_name)
        , par(_par)
    {}
    
    virtual ~FunctionCall()
    {
       delete par;
    }

    std::string getName() const
    { return name; }

    // <-- SW sp 0 ->>

    virtual bool rightFunc() const override {  return true; }

    virtual void print(std::ostream &dst) const override
    {
        dst << name;
        dst << "(";
        if (par != NULL){
            par->print(dst);
        }
        dst << ")";
    }

    virtual int countPars() const override{
        
        if (par != NULL){
            return par->countPars();
        }
        return 0;
        
    }


     virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {

        dst << ADDU(rn("sp"), rn("fp"), rn("zero")) <<std::endl; // Make sure sp is at the current fp.

        // SP = FP
        
        if (par != NULL){
            mainContext->counter = 0;
            par->compile(rn("t0"), dst, mainContext); // <---- SHIT OUT EVERYTHING 
            dst<< SW(rn("t0"), std::to_string(mainContext->counter), rn("sp")) << std::endl;

            if (mainContext->counter == 0){
                dst<< ADDU(rn("a0"), rn("t0"), rn("zero")) << std::endl;
            } else if (mainContext->counter == 4){
                dst<< ADDU(rn("a1"), rn("t0"), rn("zero")) << std::endl;
            } else if (mainContext->counter == 8){
                dst<< ADDU(rn("a2"), rn("t0"), rn("zero")) << std::endl;
            } else if (mainContext->counter == 12){
                dst<< ADDU(rn("a3"), rn("t0"), rn("zero")) << std::endl;    ///// t0 = t0 + f( t0 + t1  )
            }
        }
        
        dst << JAL(name) <<std::endl; // FUNC CALL

        dst << ADDU(destReg,rn("v0"),rn("zero")) << std::endl;    //////
    }
   
};

class FunctionCallPars
    : public FunctionCall
{
public:
    FunctionCallPars(std::string _name, BasePtr _par )
        : FunctionCall(_name, _par)
    {}
};

class FunctionCallNoPars
    : public FunctionCall
{
public:
    FunctionCallNoPars(std::string _name)
        : FunctionCall(_name, NULL)
    {}
};

#endif