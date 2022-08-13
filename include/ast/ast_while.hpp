#ifndef ast_while_hpp
#define ast_while_hpp

#include "ast.hpp"

#include <string>
#include <iostream>
// branches(eval,seq)

class While
    : public Base
{
private:
    BasePtr eval;
    BasePtr seq;
protected:
    std::string type;
    
    While(BasePtr _eval, BasePtr _seq, std::string _type)
        : eval(_eval)
        , seq(_seq)
        , type(_type)

    {}
public:

    virtual ~While()
    {
        delete eval;
        delete seq;
    }

    BasePtr getEval() const
    { return eval; }

    BasePtr getSeq() const
    { return seq; }

    virtual int countDeclares() const override{
        if(seq!=0){
            return seq->countDeclares();
        }
        return 0;
    }
    
    virtual int countPars() const override{
        int count[2] = {0, 0};

        int max = 0;

        if (eval != NULL){
            count[0] = eval->countPars();
        }
        if (seq != NULL){
            count[1] = seq->countPars();
        }
        
        for (int i = 0; i < 2; i++){
            if (count[i] > max){
                max = count[i];
            }
        }

        return max;
        

    }


    virtual void print(std::ostream &dst) const override
    {
        dst << "while ( ";
        eval->print(dst);
        dst << " ) { \n";
        if (seq!=NULL){
            seq->print(dst);
        }
        dst <<" } ";
    }
     virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        if(type=="While"){
        // Create Label Names
        std::string label_loop=makeName("loop", mainContext);
        std::string label_end=makeName("end", mainContext);

    
        mainContext->stackScope.push_back(*(new std::vector<std::pair<std::string, int>>)); // Create a new scope.
        
       
        mainContext->BreakTracker.push_back(label_end);

        // Loop Label
        dst<<label_loop<<":"<<std::endl;

        // Evaluate Condition
        eval->compile(rn("t0"),dst,mainContext);
        dst<<BEQ(rn("t0"), rn("zero"), label_end)<<std::endl;

        // Evaluate Sequence
        if (seq != NULL){
            seq->compile(rn("t9"),dst, mainContext);
        }

        // Return to top of loop
        dst<<BEQ(rn("zero"), rn("zero"), label_loop)<<std::endl;

        // Exit Label
        dst<<label_end<<":"<<std::endl;

        mainContext->BreakTracker.pop_back();
  
        mainContext->stackScope.pop_back(); // Destroy Scope
    
    
    }
}
    
};

class WhileLoop
    : public While
{
public:
    WhileLoop(BasePtr _eval, BasePtr _seq)
        : While(_eval,_seq,"While")
    {}
};

class EmptyWhileLoop
    : public While
{
public:
    EmptyWhileLoop(BasePtr _eval)
        : While(_eval,NULL,"While")
    {}
};

#endif
