#ifndef ast_parseq_hpp
#define ast_parseq_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class ParSeq
    : public Base
{
private:
    BasePtr prev;
    BasePtr eval;
    std::string id = "PAR";
public:
   
    ParSeq(BasePtr _prev, BasePtr _eval)
        : prev(_prev)
        , eval(_eval)
    
    {}
  
    virtual ~ParSeq()
    {
        delete prev;
        delete eval;
    }

    BasePtr getPrev()
    { return prev; }

    BasePtr getEval()
    { return eval; }

    virtual std::string getId() const override {return id; }

    virtual int countPars() const override{
        
        if (prev->getId() == "PAR"){
            return 1 + prev->countPars();
        } else {
            return 1;
        }
    }

    virtual void print(std::ostream &dst) const override
    {
        prev->print(dst); dst<<", "; eval->print(dst);
    }

    // TODO
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override 
    {
        
        prev->compile(rn("t0"), dst, mainContext);

        dst<< SW(rn("t0"), std::to_string(mainContext->counter), rn("sp")) << std::endl;

        if (mainContext->counter == 0){
            dst<< ADDU(rn("a0"), rn("t0"), rn("zero")) << std::endl;
        } else if (mainContext->counter == 4){
            dst<< ADDU(rn("a1"), rn("t0"), rn("zero")) << std::endl;
        } else if (mainContext->counter == 8){
            dst<< ADDU(rn("a2"), rn("t0"), rn("zero")) << std::endl;
        } else if (mainContext->counter == 12){
            dst<< ADDU(rn("a3"), rn("t0"), rn("zero")) << std::endl;
        }
        
        mainContext->counter+=4;

        eval->compile(destReg, dst, mainContext);
    }
   
};

#endif
