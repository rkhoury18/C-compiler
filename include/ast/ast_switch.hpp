#ifndef ast_switch_hpp
#define ast_switch_hpp

#include "ast.hpp"

#include <string>
#include <iostream>


class Switch
    : public Base
{
private:
    BasePtr var;
    BasePtr seq;

protected:
    Switch(BasePtr _var, BasePtr _seq)
        : var(_var)
        , seq(_seq)

    {}
public:

    virtual ~Switch()
    {
        delete var;
        delete seq;

    }

    BasePtr getVar() const
    { return var; }


    BasePtr getSeq() const
    { return seq; }


    virtual int countDeclares() const override{
        return seq->countDeclares();
    }
    
    virtual int countPars() const override{
        if (seq != NULL){
            return seq->countPars();
        }
        else{
            return 0;
        }

        

    }

    virtual void print(std::ostream &dst) const override
    {
        dst << "switch ( ";
        var->print(dst);
        dst << " ) { \n";
        seq->print(dst);
        dst <<" } ";
    }
     virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {   
        std::string label_end=makeName("loop", mainContext);
        mainContext->BreakTracker.push_back(label_end);
        
        var->compile(rn("t5"),dst,mainContext);
        seq->compile(rn("t5"),dst,mainContext);
        
         dst<<label_end<<":"<<std::endl;
        mainContext->BreakTracker.pop_back();
        
    
    }
};
    

class SwitchDef
    : public Switch
{
public:
    SwitchDef(BasePtr _var, BasePtr _seq)
        : Switch(_var,_seq)
    {}
};


#endif