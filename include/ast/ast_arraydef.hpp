#ifndef ast_arraydef_hpp
#define ast_arraydef_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class ArrayDef
    : public Base
{
private:
    BasePtr var;
    int size;
    BasePtr arrayseq;
    std::vector<BasePtr> arrayValues;

public:

    ArrayDef(BasePtr _var, int _size, BasePtr _arrayseq)
        : var(_var)
        , size(_size)
        , arrayseq(_arrayseq)
        
    {
        if (arrayseq != NULL){
            arrayseq->countEvals(&arrayValues);
        } 

        // If a size has been defined
        std::cout << size << std::endl;

        if (size != -1 && arrayseq != NULL){
            // Get the extra size needed 
            int extra = arrayValues.size() - size;

            if (extra > 0){

                // If its legal, add that many 0s
                for (int i = 0; i < extra; i++){
                    BasePtr* zero;
                    arrayValues.push_back( *zero );
                }
            }
        } else if (arrayseq == NULL) {
            for (int i = 0; i < size; i++){
                    BasePtr* zero;
                    arrayValues.push_back( *zero );
                }
        }

    }

    virtual ~ArrayDef()
    {
        delete var;
        delete arrayseq;
    }

    BasePtr getVar() const
    { return var; }

    BasePtr getArrayseq() const
    { return arrayseq; }

    int getSize() const
    { return size; }

    virtual void print(std::ostream &dst) const override
    {
        dst << "int ";
        var->print(dst);
        dst << " [ "; dst << size;
        dst<< " ] ";
        if (arrayseq != NULL){
            dst<<" = { ";
            arrayseq->print(dst);
            dst<<" } ";
        }
        
    }

    virtual int countDeclares() const override{

        return arrayValues.size();

    }
    
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        // FUNCTION <-- Get Size and Values
        // vector --> EVALS
        std::cout << arrayValues.size() << std::endl;
        for (int values = 0; values < arrayValues.size(); values++){

            if (arrayValues.at(values)!=NULL){
                 arrayValues.at(values)->compile(rn("t0"), dst, mainContext); // Evaluate assigned value
            } else {
                dst << ADDU(rn("t0"), rn("zero"), rn("zero"));
            }
           
            dst << SW(rn("t0"), std::to_string(mainContext->offset), rn("sp"))<<std::endl; // Store the variable

            std::pair<std::string, int> newVar = std::make_pair( (var->getId()+"["+std::to_string(values)+"]"), mainContext->offset); // Create a pair with the variable name and offset
            
            // Add to most current scope.
            mainContext->stackScope.back().push_back( newVar ); // 

            mainContext->offset+=4; // Make next variable be written to a new location in the stack
           
        }

        // Should have a full vector of values now.

    }
};

class ArSize
    : public ArrayDef
{
public:
    ArSize(BasePtr _var, int _size)
        : ArrayDef(_var, _size, NULL)
    {}
};

class ArAssign
    : public ArrayDef
{
public:
    ArAssign(BasePtr _var, BasePtr _arrayseq)
        : ArrayDef(_var, -1, _arrayseq)
    {}
};

class ArSizeAssign
    : public ArrayDef
{
public:
    ArSizeAssign(BasePtr _var, int _size, BasePtr _arrayseq)
        :ArrayDef(_var, _size, _arrayseq)
    {}
};

class ArSizeAssignOne
    : public ArrayDef
{
public:
    ArSizeAssignOne(BasePtr _var, int _size, BasePtr _arrayseq)
        :ArrayDef(_var, _size, _arrayseq)
    {}
};

class ArAssignOne
    : public ArrayDef
{
public:
    ArAssignOne(BasePtr _var, BasePtr _arrayseq)
        :ArrayDef(_var,-1, _arrayseq)
    {}
};

#endif
