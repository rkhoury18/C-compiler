#ifndef ast_if_hpp
#define ast_if_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class If
    : public Base
{
private:
    BasePtr eval;
    BasePtr seq;
    BasePtr elseseq;
protected:
    If(BasePtr _eval, BasePtr _seq, BasePtr _elseseq)
        : eval(_eval)
        , seq(_seq)
        , elseseq(_elseseq)
        
    {}
public:

    virtual ~If()
    {
        delete eval;
        delete seq;
        delete elseseq;
    }

    BasePtr getEval() const
    { return eval; }

    BasePtr getSeq() const
    { return seq; }

    BasePtr getElseseq() const 
    { return elseseq; }

    virtual int countDeclares() const override{
        if (elseseq != NULL){
            return seq->countDeclares() + elseseq->countDeclares();
        }
        return seq->countDeclares();
    }
    
     virtual int countPars() const override{

        int count[3] = {0, 0, 0};

        int max = 0;

        if (eval != NULL){
            count[0] = eval->countPars();
        }
        if (seq != NULL){
            count[1] = seq->countPars();
        }
        if (elseseq != NULL){
            count[2] = elseseq->countPars();
        }


        for (int i = 0; i < 3; i++){
            if (count[i] > max){
                max = count[i];
            }
        }

        return max;
   
  
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << "if ( ";
        eval->print(dst);
        dst << " ) { \n";
        seq->print(dst);
        dst << "} \n";
        if (elseseq!=NULL){
            dst << " else { \n";
            elseseq->print(dst);
            dst << "} \n";
        }
    
    }
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        std::string label_else=makeName("else", mainContext );
        std::string label_end=makeName("end", mainContext );

        mainContext->BreakTracker.push_back(label_end);
        mainContext->stackScope.push_back(*(new std::vector<std::pair<std::string, int>>)); // Create a new scope.

        // Evaluate Condition
        eval->compile(rn("t0"), dst, mainContext);

        // Check Else condition Condition
        dst<<BEQ(rn("zero"), rn("t0"), label_else)<< std::endl;

        // If Eval: Evaluation will be dealt with within the sequence.
        if(seq != NULL){
            seq->compile(rn("t9"), dst, mainContext);
        }

        // End the IF statement
        dst<<BEQ(rn("zero"), rn("zero"), label_end)<<std::endl;

        // Else Eval
        dst<<label_else<<":"<<std::endl;
        if (elseseq != NULL){
            elseseq->compile(rn("t9"), dst, mainContext);
        }

        // END IF STATEMENT
        dst<<label_end<<":"<<std::endl;

        mainContext->stackScope.pop_back(); // Destroy Scope
        mainContext->BreakTracker.pop_back();

    }
};
class WithElse
    : public If
{
public:
    WithElse(BasePtr _eval, BasePtr _seq, BasePtr _elseseq)
        : If(_eval, _seq, _elseseq)
    {}
};

class WithoutElse
    : public If
{
public:
    WithoutElse(BasePtr _eval, BasePtr _seq)
        : If(_eval, _seq, NULL)
    {}
};

class NoCurlyElse
    : public If
{
public:
    NoCurlyElse(BasePtr _eval, BasePtr _seq, BasePtr _elseseq)
        : If(_eval, _seq, _elseseq)
    {}
};

class NoCurlyNoElse
    : public If
{
public:
    NoCurlyNoElse(BasePtr _eval, BasePtr _seq)
        : If(_eval, _seq, NULL)
    {}
};

class IfLine
    : public If
{
public:
    IfLine(BasePtr _eval, BasePtr _seq, BasePtr _elseseq)
        : If(_eval, _seq, _elseseq)
    {}
};

class ElseLine
    : public If
{
public:
    ElseLine(BasePtr _eval, BasePtr _seq,BasePtr _elseseq)
        : If(_eval, _seq, _elseseq)
    {}
};




class WithElseEmptyIf
    : public If
{
public:
    WithElseEmptyIf(BasePtr _eval, BasePtr _elseseq)
        : If(_eval,NULL, _elseseq)
    {}
};
class WithElseEmptyElse
    : public If
{
public:
    WithElseEmptyElse(BasePtr _eval, BasePtr _seq)
        : If(_eval,_seq,NULL)
    {}
};

class WithoutElseEmptyIf
    : public If
{
public:
    WithoutElseEmptyIf(BasePtr _eval)
        : If(_eval,NULL, NULL)
    {}
};

class NoCurlyElseEmptyIf
    : public If
{
public:
    NoCurlyElseEmptyIf(BasePtr _eval, BasePtr _elseseq)
        : If(_eval,NULL, _elseseq)
    {}
};
class NoCurlyElseEmptyElse
    : public If
{
public:
    NoCurlyElseEmptyElse(BasePtr _eval, BasePtr _seq)
        : If(_eval,_seq, NULL)
    {}
};
class NoCurlyNoElseEmptyIf
    : public If
{
public:
    NoCurlyNoElseEmptyIf(BasePtr _eval)
        : If(_eval,NULL,NULL)
    {}
};

class IfLineElseEmpty
    : public If
{
public:
    IfLineElseEmpty(BasePtr _eval, BasePtr _seq)
        : If(_eval, _seq, NULL)
    {}
};
class ElseLineIfEmpty
    : public If
{
public:
    ElseLineIfEmpty(BasePtr _eval, BasePtr _elseseq)
        : If(_eval,NULL, _elseseq)
    {}
};

class Ifnewcase
    : public If
{
public:
    Ifnewcase(BasePtr _eval)
        : If(_eval,NULL,NULL)
    {}
};

class Ifnewercase
    : public If
{
public:
    Ifnewercase(BasePtr _eval)
        : If(_eval,NULL,NULL)
    {}
};

class IfBothEmpty
    : public If
{
public:
    IfBothEmpty(BasePtr _eval)
        : If(_eval,NULL,NULL)
    {}
};

class IfBothEmptyNew
    : public If
{
public:
    IfBothEmptyNew(BasePtr _eval)
        : If(_eval,NULL,NULL)
    {}
};







#endif
