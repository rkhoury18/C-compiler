#ifndef ast_blockdec_hpp
#define ast_blockdec_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class BlockDec
    : public Base
{
private:
    BasePtr name;
    BasePtr args;
    BasePtr seq;
    std::string type;
    
protected:
    BlockDec(BasePtr _name, BasePtr _args, BasePtr _seq, std::string _type)
        : name(_name)
        , args(_args)
        , seq(_seq)
        , type(_type)
    {}
public:
  
    virtual ~BlockDec()
    {
        delete name;
        delete seq;
    }

    BasePtr getName()
    { return name; }

    BasePtr getSeq()
    { return seq; }

    virtual void print(std::ostream &dst) const override
    {
        dst << type;
        name->print(dst);
        dst << "(";
        if (args != NULL){
            args->print(dst);
        }
        dst << "){"; 
        dst << "\n";
        if (seq != NULL){
            seq->print(dst);
        }
        dst << "}\n";
    } 
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {

        mainContext->scopeOffsets.push_back(mainContext->offset); // Remove offset
        mainContext->currentFunc.push_back(name->getId());
        mainContext->offset = 0;

        mainContext->stackScope.push_back(*(new std::vector<std::pair<std::string, int>>)); // Create a new scope.
        int size = 8;
        int parSize = 16;


        dst << ".globl " << name->getId() << std::endl;
        dst<<name->getId()<<":"<<std::endl; // Function Label

        // PARSIZE 16 <-- 4 memory locs ar filled

        // SP = FP

        // COMPILING SEQ FOR SOME REASON

        if (seq != NULL){
             size = 4*(2+seq->countDeclares()); // Get the size required for the stack frame

             int parTemp = 4*(1+seq->countPars()); // Max number of Pars

             if (parTemp > parSize){
                 parSize = parTemp;
             }

             size = size + parSize;
             mainContext->offset = parSize;

             if (args != NULL){
                mainContext->counter = size;
                mainContext->counter2 = 0;
                args->compile("NULL", dst, mainContext);
            }
        }

        dst << ADDIU(rn("sp"), rn("sp"), std::to_string(-1*size) ) <<std::endl; // Set Stack Frame
        dst << SW(rn("ra"), std::to_string(size-4), rn("sp")) <<std::endl; // Store return 
        dst << SW(rn("fp"), std::to_string(size-8), rn("sp")) <<std::endl; // Store frame pointer
        dst << ADDU(rn("fp"), rn("sp"), rn("zero")) <<std::endl; // Set FP to SP
        
        if (seq != NULL){
            seq->compile("NULL", dst, mainContext); // Instructions that come after
        }

        dst<<"kill_"<<name->getId()<<":"<<std::endl;
        
        dst << ADDU(rn("sp"), rn("fp"), rn("zero")) <<std::endl; // reset SP to FP
        dst << LW(rn("ra"), std::to_string(size-4), rn("sp")) <<std::endl; // Load Return
        dst << LW(rn("fp"), std::to_string(size-8), rn("sp")) <<std::endl; // Load frame pointer
        dst << ADDIU(rn("sp"), rn("sp"), std::to_string(size)) <<std::endl; // Destroy Stack Frame
    
        dst<< JR(rn("ra")) <<std::endl; // Return

        mainContext->stackScope.pop_back(); // Destroy Scope
        mainContext->offset = mainContext->scopeOffsets.back(); // Restore Offset
        mainContext->scopeOffsets.pop_back();
        mainContext->currentFunc.pop_back(); // Remove func reference
        
        //lRFT NUMBER 2
    }
};


class VoidFunction
    : public BlockDec
{
public:
    VoidFunction(BasePtr _name, BasePtr _seq)
        : BlockDec(_name, NULL, _seq, "void")
    {}
};
class VoidEmptyFunction
    : public BlockDec
{
public:
    VoidEmptyFunction(BasePtr _name)
        : BlockDec(_name, NULL, NULL, "void")
    {}
};

class IntFunction
    : public BlockDec
{
public:
    IntFunction(BasePtr _name, BasePtr _seq)
        : BlockDec(_name, NULL, _seq, "int")
    {}
};


class VoidFunctionArgs
    : public BlockDec
{
public:
    VoidFunctionArgs(BasePtr _name,BasePtr _args, BasePtr _seq)
        : BlockDec(_name, _args, _seq, "void")
    {}
};
class VoidEmptyFunctionArgs
    : public BlockDec
{
public:
    VoidEmptyFunctionArgs(BasePtr _name, BasePtr _args)
        : BlockDec(_name, _args, NULL, "void")
    {}
};

class IntFunctionArgs
    : public BlockDec
{
public:
    IntFunctionArgs(BasePtr _name, BasePtr _args, BasePtr _seq)
        : BlockDec(_name, _args,_seq, "int")
    {}
};


#endif
