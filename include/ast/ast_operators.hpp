#ifndef ast_operators_hpp
#define ast_operators_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class Operator
    : public Base
{
private:
    BasePtr left;
    BasePtr right;
    std::string type;
protected:
    Operator(BasePtr _left, BasePtr _right, std::string _type)
        : left(_left)
        , right(_right)
        , type(_type)
      
    {}
public:

    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const =0;

    BasePtr getLeft() const
    { return left; }

    BasePtr getRight() const
    { return right; }
    

    virtual void print(std::ostream &dst) const override
    {
        dst<<"( ";
        left->print(dst);
        dst<<" ";
        dst<<getOpcode();
        dst<<" ";
        right->print(dst);
        dst<<" )";
    }

    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        if (type=="Sub"){

            // Evaluate the left and right sub-trees

            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }
            
            // Evaluate the value 
            dst<< SUB(destReg, rn("t0"), rn("t1")) <<std::endl;
            
        }
        else if (type=="Add"){

            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            dst<<ADDU(destReg, rn("t0"), rn("t1"))<<std::endl;
            
        }
        else if (type=="Less"){
            
            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            dst<<SLT(destReg, rn("t0"), rn("t1"))<<std::endl;

        }
        else if(type=="Mul"){
            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            dst<<MUL(destReg,rn("t0"), rn("t1"))<<std::endl;
        }
        else if(type=="Div"){

            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            dst<<DIV(rn("t0"), rn("t1"))<<std::endl;
        }
        else if (type=="LessEqual"){ ///??        
            
            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }


            dst<<SLT(rn("t0"), rn("t1"), rn("t0"))<<std::endl;
            dst<<XORI(destReg, rn("t0"), "0x0001")<<std::endl;
           
        }
        else if (type=="Equal"){

            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            dst<<XOR(rn("t0"), rn("t0"), rn("t1"))<<std::endl;
            dst<<SLTIU(destReg, rn("t0"), "0x0001")<<std::endl;
        }
        else if (type=="Notequal"){

            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            dst<<XOR(rn("t0"), rn("t0"), rn("t1"))<<std::endl;
            dst<<SLTIU(destReg, "0x0000", rn("t0"))<<std::endl;
        }
        else if (type=="Greater"){

            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            dst<<SLT(destReg, rn("t1"), rn("t0"))<<std::endl;
        }
        else if (type=="GreaterEqual"){

            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            dst<<SLT(rn("t0"), rn("t0"), rn("t1"))<<std::endl;
            dst<<XORI(destReg, rn("t0"), "0x0001")<<std::endl;
        }
        else if (type=="BitAnd"){

            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            dst<<AND(destReg, rn("t0"), rn("t1"))<<std::endl;
        }
        else if (type=="BitOr"){

            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            dst<<OR(destReg, rn("t0"), rn("t1"))<<std::endl;
        }
        else if (type=="And"){
            
            // Need to turn these into booleans. 
            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            // t0 = 0 < t0
            dst<<SLTU(rn("t0"), rn("zero"), rn("t0"))<<std::endl;
            dst<<SLTU(rn("t1"), rn("zero"), rn("t1"))<<std::endl;

            dst<<AND(destReg, rn("t0"), rn("t1"))<<std::endl;

        }
        else if (type=="Or"){

            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            // t0 = 0 < t0
            dst<<SLTU(rn("t0"), rn("zero"), rn("t0"))<<std::endl;
            dst<<SLTU(rn("t1"), rn("zero"), rn("t1"))<<std::endl;
            
            dst<<OR(destReg, rn("t0"), rn("t1"))<<std::endl;
        }
          else if (type=="Xor"){

            left->compile(rn("t0"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t7"), rn("t0"), rn("zero")) << std::endl;
            }
            right->compile(rn("t1"), dst, mainContext);
            if (right->rightFunc()){
                dst << ADDU(rn("t0"), rn("t7"), rn("zero")) << std::endl;
            }

            dst<<XOR(destReg, rn("t0"), rn("t1"))<<std::endl;
            
        }
    }
};

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    
    AddOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right, "Add" )
    {}
};

class MinusOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
public:
   
    MinusOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"Sub")
    {}
};

class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
public:
    
    MulOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"Mul")
    {}
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
public:
    
    DivOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right, "Div")
    {}
};

class GROperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return ">"; }
public:
    
    GROperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right, "Greater")
    {}
};

class LEOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "<"; }
public:
     
    LEOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"Less")
    {}
};

class GREQOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return ">="; }
public:
     
    GREQOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"GreaterEqual")
    {}
};

class LEEQOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "<="; }
public:
    
    LEEQOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"LessEqual")
    {}
};

class EQOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "=="; }
public:
     
    EQOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"Equal")
    {}
};

class NEQOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "!="; }
public:
    
    NEQOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"NotEqual")
    {}
};

class BitANDOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "&"; }
public:
    
    BitANDOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"BitAnd")
    {}
};

class BitOROperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "|"; }
public:
  
    BitOROperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"BitOr")
    {}
};

class ANDOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "&&"; }
public:
     
    ANDOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"And")
    {}
};

class OROperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "||"; }
public:

    OROperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"Or")
    {}
};

class BitXorOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "^"; }
public:

    BitXorOperator(BasePtr _left, BasePtr _right)
        : Operator(_left, _right,"Xor")
    {}
};



#endif
