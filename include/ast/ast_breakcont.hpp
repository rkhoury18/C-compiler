#ifndef ast_breakcont_hpp
#define ast_breakcont_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class Break_Cont
    : public Base
{
private:


public:
    std::string type;
    Break_Cont(std::string _type)
       : type(_type)
    {}
   



    virtual void print(std::ostream &dst) const override
    {
        if (type=="Break"){
            dst<<" break ; ";
        }
        if (type=="Cont"){
            dst<<" continue ; ";
        }

    }
    
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {   
        if (type=="Break"){
            dst<<BEQ(rn("zero"), rn("zero"), mainContext->BreakTracker.back())<<std::endl;
        }
        if (type=="Cont"){
            dst<<BEQ(rn("zero"), rn("zero"), mainContext->LoopTracker.back())<<std::endl;
        }


    }
};

class Break
    : public Break_Cont
{
public:
    Break( )
        : Break_Cont("Break")
    {}
};

class Cont
    : public Break_Cont
{
public:
    Cont( )
        : Break_Cont("Cont")
    {}
};



#endif