#ifndef ast_for_hpp
#define ast_for_hpp

#include "ast.hpp"

#include <string>
#include <iostream>


class For
    : public Base
{
private:
    BasePtr line;
    BasePtr eval;
    BasePtr forarg;
    BasePtr seq;
protected:
    For(BasePtr _line, BasePtr _eval, BasePtr _forarg, BasePtr _seq)
        : line(_line)
        , eval(_eval)
        , forarg(_forarg)
        , seq(_seq)

    {}
public:

    virtual ~For()
    {
        delete line;
        delete eval;
        delete forarg;
        delete seq;
    }

    BasePtr getEval() const
    { return eval; }

    BasePtr getSeq() const
    { return seq; }

    BasePtr getForarg() const
    { return forarg; }

    BasePtr getline() const
    { return line; }

    virtual int countDeclares() const override{
        if (seq != NULL){
            return seq->countDeclares();
        }
        return 0;

    }
    
    virtual int countPars() const override{
        
        int count[4] = {0, 0, 0, 0};

        int max = 0;

        if (line != NULL){
            count[0] = line->countPars();
        }
        if (eval != NULL){
            count[1] = eval->countPars();
        }
        if (forarg != NULL){
            count[2] = forarg->countPars();
        }
        if (seq != NULL){
            count[3] = seq->countPars();
        }
        
        for (int i = 0; i < 4; i++){
            if (count[i] > max){
                max = count[i];
            }
        }

        return max;
    
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << "for ( ";
        if(line!=NULL){
           line->print(dst);
        }
        eval->print(dst);
        dst << " ; ";
        if (forarg!=NULL){
            forarg->print(dst);
        }
        dst << " ) { \n";
        if (seq != NULL){
            seq->print(dst);
        }
        dst <<" } ";
    }
     virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    { 
        // Create Label Names
        std::string label_loop=makeName("loop", mainContext);
        std::string label_end=makeName("end", mainContext);
        std::string label_continue=makeName("continue",mainContext);

        mainContext->BreakTracker.push_back(label_continue);
        mainContext->LoopTracker.push_back(label_loop);
        mainContext->stackScope.push_back(*(new std::vector<std::pair<std::string, int>>)); // Create a new scope.

        // Loop Label
        if (line != NULL){
            line->compile(rn("t0"),dst,mainContext);
        }

        dst<<label_loop<<":"<<std::endl;

        // Evaluate Condition
        eval->compile(rn("t1"),dst,mainContext);
        dst<<BEQ(rn("t1"), rn("zero"), label_end)<<std::endl;

        // Evaluate Sequence
        if (seq != NULL){
            seq->compile(rn("t9"),dst, mainContext);
        }
        dst<<label_continue<<":"<<std::endl;


        if (forarg != NULL){
            forarg->compile(rn("t2"),dst,mainContext);
        }

        // Return to top of loop
        dst<<BEQ(rn("zero"), rn("zero"), label_loop)<<std::endl;

        // Exit Label
        dst<<label_end<<":"<<std::endl;

        mainContext->stackScope.pop_back(); // Destroy Scope 
        mainContext->BreakTracker.pop_back();
        mainContext->LoopTracker.pop_back();
  
    }
};
    


class ForFull
    : public For
{
public:
    ForFull(BasePtr _line, BasePtr _eval, BasePtr _forarg, BasePtr _seq)
        : For(_line,_eval,_forarg,_seq)
    {}
};

class ForNoLine
    : public For
{
public:
    ForNoLine(BasePtr _eval, BasePtr _forarg, BasePtr _seq)
        : For(NULL,_eval,_forarg,_seq)
    {}
};

class ForNoForArg
    : public For
{
public:
    ForNoForArg(BasePtr _line, BasePtr _eval, BasePtr _seq)
        : For(_line,_eval,NULL,_seq)
    {}
};

class ForNothing
    : public For
{
public:
    ForNothing(BasePtr _line, BasePtr _seq)
        : For(_line,NULL,NULL,_seq)
    {}
};

class ForEmptyFull
    : public For
{
public:
    ForEmptyFull(BasePtr _line, BasePtr _eval, BasePtr _forarg)
        : For(_line,_eval,_forarg,NULL)
    {}
};

class ForEmptyNoLine
    : public For
{
public:
    ForEmptyNoLine(BasePtr _eval, BasePtr _forarg)
        : For(NULL,_eval,_forarg,NULL)
    {}
};

class ForEmptyNoForArg
    : public For
{
public:
    ForEmptyNoForArg(BasePtr _line, BasePtr _eval)
        : For(_line,_eval,NULL,NULL)
    {}
};

class ForEmptyNothing
    : public For
{
public:
    ForEmptyNothing(BasePtr _line)
        : For(_line,NULL,NULL,NULL)
    {}
};
#endif