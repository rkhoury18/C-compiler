#ifndef ast_values_hpp
#define ast_values_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class Variable
    : public Base
{
private:
    std::string id;
    
public:

    Variable(const std::string &_id)
        : id(_id)
    {}

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
    }
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
        if (destReg != "NULL"){
            dst<< LW(destReg, std::to_string(findVar(id,mainContext)), rn("sp")) << std::endl;
        } else {
            std::pair<std::string, int> newVar = std::make_pair(id, mainContext->counter); // Create a pair with the variable name and offset
        
            std::cout << id << std::endl;

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

        
        
    }
    virtual std::string getId() const override {return id; }

};

class Number
    : public Base
{
private:
    int value;
public:
   
    Number(int _value)
        : value(_value)
    {}

    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {

        // Convert INT into a HEX value
        std::string valAsHex = convertInt(value);

        // Load upper 4 hex values
        dst<<LUI(rn("t8"), "0x"+valAsHex.substr(0,4))<<std::endl;
        
        // Load last 4 values, and combine.
        dst<<ORI(destReg, rn("t8"), "0x"+valAsHex.substr(4,8))<<std::endl;
        
    }
};


#endif
