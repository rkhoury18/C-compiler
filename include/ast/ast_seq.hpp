#ifndef ast_seq_hpp
#define ast_seq_hpp

#include "ast.hpp"
//branches(preb,lineDec)

#include <string>
#include <iostream>

class Seq
    : public Base
{
private:
    BasePtr prev;
    BasePtr lineDec;
public:
   
    Seq(BasePtr _prev, BasePtr _lineDec)
        : prev(_prev)
        , lineDec(_lineDec)
    
    {}
  
    
    virtual ~Seq()
    {
        delete prev;
        delete lineDec;
    }

    BasePtr getPrev()
    { return prev; }

    BasePtr getLineDec()
    { return lineDec; }

    virtual int countDeclares() const override{
        return prev->countDeclares() + lineDec->countDeclares();
    }

    virtual int countPars() const override{

        std::cout << "ONE" << std::endl;
        
        int prevCount = prev->countPars();
        int lineDecCount = lineDec->countPars();
        
        if (prevCount > lineDecCount){
            return prevCount;
        } else {
            return lineDecCount;
        }
    }

    virtual void print(std::ostream &dst) const override
    {
        prev->print(dst);
        lineDec->print(dst);
    }

    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        prev->compile("NULL",dst,mainContext);
        lineDec->compile("NULL",dst,mainContext);
    }
   
};


#endif
