#ifndef ast_argseq_hpp
#define ast_argseq_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class ArgSeq
    : public Base
{
private:
    BasePtr prev;
    BasePtr eval;
public:
   
    ArgSeq(BasePtr _prev, BasePtr _eval)
        : prev(_prev)
        , eval(_eval)
    
    {}
  
    virtual ~ArgSeq()
    {
        delete prev;
        delete eval;
    }

    BasePtr getPrev()
    { return prev; }

    BasePtr getEval()
    { return eval; }

    virtual void print(std::ostream &dst) const override
    {
        prev->print(dst); dst<<", "; eval->print(dst);
    }

    virtual std::string getId() const override 
    {
        return prev->getId(); 
    }

    // TODO
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override 
    {
        prev->compile("NULL", dst, mainContext); // GET ARGS LEFT

        std::pair<std::string, int> newVar = std::make_pair(eval->getId(), mainContext->counter); // Create a pair with the variable name and offset
        
        // Add to most current scope.
        mainContext->stackScope.back().push_back( newVar ); // 

        if (mainContext->counter2 == 0){
            dst << SW(rn("a0"), "0", rn("fp")) << std::endl;
        } else if (mainContext->counter2 == 1){
            dst << SW(rn("a1"), "4", rn("fp")) << std::endl;
        } else if (mainContext->counter2 == 2){
            dst << SW(rn("a2"), "8", rn("fp")) << std::endl;
        } else if (mainContext->counter2 == 3){
            dst << SW(rn("a3"), "12", rn("fp")) << std::endl;
        }

        mainContext->counter2++;

        mainContext->counter+=4; // Make next variable be written to a new location in the stack
    }
   
};

#endif
