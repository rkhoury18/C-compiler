#ifndef ast_arrayseq_hpp
#define ast_arrayseq_hpp

#include "ast.hpp"

#include <string>
#include <iostream>
#include <vector>

class ArraySeq
    : public Base
{
private:
    BasePtr prev;
    BasePtr num;
public:
   
    ArraySeq(BasePtr _prev, BasePtr _num)
        : prev(_prev)
        , num(_num)
    
    {}
  
    virtual ~ArraySeq()
    {
        delete prev;
        delete num;

    }

    BasePtr getPrev()
    { return prev; }

    BasePtr getNum()
    { return num; }

    virtual void countEvals(std::vector<BasePtr> *currentList) const override
    {  
        prev->countEvals(currentList);
        num->countEvals(currentList);
    }

    virtual void print(std::ostream &dst) const override
    {
        prev->print(dst); dst<<", "; num->print(dst);
    }

    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {

    }


   
};

#endif
