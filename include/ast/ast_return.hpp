#ifndef ast_return_hpp
#define ast_return_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class Return
    : public Base
{
private:
    BasePtr eval;
public:

    Return(BasePtr _eval)
        : eval(_eval)
        
    {}

    virtual ~Return()
    {
        delete eval;
    }

    BasePtr getEval() const
    { return eval; }

    virtual void print(std::ostream &dst) const override
    {
        dst << "return ";
        eval->print(dst);
        dst << ";\n";
    }

    virtual int countPars() const override{
        
        return eval->countPars();
    }

    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        eval->compile(rn("v0"),dst,mainContext);
        dst<<BEQ(rn("zero"), rn("zero"), "kill_"+mainContext->currentFunc.back())<<std::endl;
    }
  
  
};

#endif