#ifndef ast_base_hpp
#define ast_base_hpp

#include <string>
#include <iostream>
#include <vector>

#include "ast.hpp"

class Base;

typedef const Base *BasePtr;

class Base
{
public:
    virtual ~Base()
    {}
    //! Tell and expression to print itself to the given stream
    virtual void print(std::ostream &dst) const =0;

    // Tell AST Node to print out the required MIPS code
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const =0;

    // Tell AST Node to indicate that it is a Declcare
    virtual int countDeclares() const {  return 0; }

    virtual int countPars() const {  return 0; }

    virtual bool rightFunc() const {  return false; }

    virtual void countEvals(std::vector<BasePtr> *currentList) const { };

    virtual std::string getId() const { return "NULL"; }


    // HELPER FUNCTIONS ----------------

    // Unique Jump Labelling
    std::string makeName(std::string base, context* mainContext) const
    {
        return base+std::to_string(mainContext->makeNameUnq++);
    }

    // Deal with funky register names
    std::string rn(std::string reg) const
    {
            if(reg=="zero"){
            return "$0";  
            }  //Always 0
            else if(reg=="v0"){
                return "$2";
            }
            else if (reg=="v1"){
                return "$3";
            }
            else if (reg=="a0"){
            return "$4"; 
            }
            else if (reg=="a1"){
                return "$5";
            }
            else if (reg=="a2"){
                return "$6";
            }
            else if (reg=="a3"){
                return "$7";
            }
            else if (reg=="t0"){
            return "$8";
            }
            else if (reg=="t1"){
            return "$9";
            }
            else if(reg=="t2"){
                return "$10";
            }
            else if(reg=="t3"){
                return "$11";
            }
            else if(reg=="t4"){
                return "$12";
            }
            else if (reg=="t5"){
                return "$13";
            }
            else if(reg=="t6"){
                return "$14";
            }
            else if (reg=="t7"){
                return "$15";
            }
            else if (reg=="t8"){
                return "$24"; 
            }
            else if (reg=="t9"){
                return "$25";
            }
            else if (reg=="ra"){
                return "$31";
            }
            else if (reg=="sp"){
                return "$29";
            } else if (reg=="fp"){
                return "$30";
            } else {
                return "$2";
            }
    
    }

    // Convert a DEC to a HEX

    std::string decToHex(int num) const {
        switch(num){
            case 10: return "a";
            case 11: return "b";
            case 12: return "c";
            case 13: return "d";
            case 14: return "e";
            case 15: return "f";
            default: return std::to_string(num);
        }
    }

    // Convert a multi-digit DEC to HEX

    std::string convertInt(int val) const {
        std::string output = "";
        for (int i = 0; i < 8; i++){
        output += decToHex((val & 4026531840)>>28);
        val = val << 4;
        }
        return output;
    }

    // Get the offset for a variable
    
    int findVar(std::string name, context* currContext) const {

        // Find the first pair from the back containing the name. --> Get the corresponding offset value

        for ( int scopes = currContext->stackScope.size()-1; scopes >= 0; scopes-- ){ // Navigate top scope first
            for ( int vars = currContext->stackScope.at(scopes).size()-1; vars >= 0; vars-- ){ // Most recent assigned variable first.
                if ( currContext->stackScope.at(scopes).at(vars).first == name ){
                    return currContext->stackScope.at(scopes).at(vars).second; // Found?
                }
            }
        }
    }
    
    // HELPER FUNCTIONS

};

#endif