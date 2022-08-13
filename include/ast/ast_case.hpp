#ifndef ast_case_hpp
#define ast_case_hpp

#include "ast.hpp"

#include <string>
#include <iostream>


class Case
    : public Base
{
private:
    BasePtr num;
    BasePtr seq;
protected:
    std::string type;
    Case(BasePtr _num, BasePtr _seq,std::string _type)
        : num(_num)
        , seq(_seq)
        , type(_type)

    {}
public:

    virtual ~Case()
    {
        delete seq;
        delete num;
 
    }

    BasePtr getNum() const
    { return num; }

    BasePtr getSeq() const
    { return seq; }

    std::string gettype() const
    {return type; }


    virtual int countDeclares() const override{
        return seq->countDeclares();
    }

    virtual void print(std::ostream &dst) const override
    {
        if (type=="case"){
            dst << "case " << num;
        }
        if (type=="default"){
            dst<<" default ";
        }
        dst << " : ";
        if(seq!=NULL){
            dst << " {  \n";
            seq->print(dst);
            dst << " } \n ";
        }
        
    }
     virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {   
        std::string label_end=makeName("end", mainContext);
        if (type != "default"){
        if (num!=NULL){
            num->compile(rn("t0"),dst,mainContext);
        }
        dst<<BNE(rn("t0"),destReg,label_end)<<std::endl;
        if (seq!= NULL){
            seq->compile(destReg,dst,mainContext);
        }
        dst<<label_end<<":"<<std::endl;
        }
        else{
            seq->compile(destReg,dst,mainContext);
        }
    
    }
};
    

class CaseLine
    : public Case
{
public:
    CaseLine(BasePtr _num, BasePtr _seq)
        : Case(_num,_seq,"case")
    {}
};

class CaseEmpty
    : public Case
{
public:
    CaseEmpty(BasePtr _num)
        : Case(_num,NULL,"case")
    {}
};

class CaseFull
    : public Case
{
public:
    CaseFull(BasePtr _num, BasePtr _seq)
        : Case(_num,_seq,"case")
    {}
};




class Default
    : public Case
{
public:
    Default(BasePtr _seq)
        : Case(NULL,_seq,"default")
    {}
};

class DefaultEmpty
    : public Case
{
public:
    DefaultEmpty()
        : Case(NULL,NULL,"default")
    {}
};



#endif