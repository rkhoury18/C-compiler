#ifndef ast_line_hpp
#define ast_line_hpp

#include "ast.hpp"

#include <string>
#include <iostream>

class Line
    : public Base
{
private:
    BasePtr arg;

public:

     Line(BasePtr _arg)
        : arg(_arg)
    {}
    virtual ~Line()
    {
        delete arg;
    }

    BasePtr getArg()
    { return arg; }

    virtual int countDeclares() const override{
        return arg->countDeclares();
    }
    virtual int countPars() const override{

        if (arg != NULL){
            return arg->countPars();
        }
        else{
            return 0;
        }

    }

    virtual void print(std::ostream &dst) const override
    {
        arg->print(dst);
        dst << "; \n";
    }
    virtual void compile(std::string destReg, std::ostream &dst, context* mainContext) const override
    {
           // Doesn't acc do anything - has no return (a line doesn't return anything.)
            arg->compile("NULL", dst, mainContext);
    }

};


#endif
