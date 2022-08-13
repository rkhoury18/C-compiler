#ifndef ast_caseseq_hpp
#define ast_caseseq_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class CaseSeq
    : public Base
{
private:
    BasePtr prev;
    BasePtr cases;
public:
   
    CaseSeq(BasePtr _prev, BasePtr _cases)
        : prev(_prev)
        , cases(_cases)
    
    {}
  
    virtual ~CaseSeq()
    {
        delete prev;
        delete cases;
    }

    BasePtr getPrev()
    { return prev; }

    BasePtr getCases()
    { return cases; }

    virtual void print(std::ostream &dst) const override
    {
        prev->print(dst);
        dst << "\n";
        cases->print(dst);
    }

    // TODO
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override 
    {
        prev->compile(destReg,dst,mainContext);
        cases->compile(destReg,dst,mainContext);
    }
   
};

#endif
