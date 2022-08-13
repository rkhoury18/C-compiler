#ifndef ast_blockseq_hpp
#define ast_blockseq_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class BlockSeq
    : public Base
{
private:
    BasePtr prev;
    BasePtr blockDec;
public:
    
    
    BlockSeq(BasePtr _prev, BasePtr _blockDec)
        : prev(_prev)
        , blockDec(_blockDec)
        
    {}

    virtual ~BlockSeq()
    {
        delete prev;
        delete blockDec;
    }

    BasePtr getPrev()
    { return prev; }

    BasePtr getBlockDec()
    { return blockDec; }

    virtual void print(std::ostream &dst) const override
    {
        prev->print(dst);
        blockDec->print(dst);
    }
       virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
         // Print Code for Left and Right Branches
        prev->compile("NULL", dst, mainContext);
        blockDec->compile("NULL", dst, mainContext);

    }
};


#endif
