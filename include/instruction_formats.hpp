#ifndef instruction_formats_hpp
#define instruction_formats_hpp

#include "ast.hpp"
#include <string>
#include<iostream>
#include <vector>
/*
static std::string FUNC_NAME(std::string par1, std::string par2, std::string par3){

}
*/
// Register 3 Par

static std::string ADDU(std::string rd, std::string rs, std::string rt){
    return "addu "+rd+", "+rs+", "+rt;
}
static std::string SUB(std::string rd, std::string rs, std::string rt){
    return "sub "+rd+", "+rs+", "+rt;
}
static std::string SLTU(std::string rd, std::string rs, std::string rt){
    return "sltu "+rd+", "+rs+", "+rt;
}
static std::string NOR(std::string rd, std::string rs, std::string rt){
    return "nor "+rd+", "+rs+", "+rt;
}
static std::string OR(std::string rd, std::string rs, std::string rt){
    return "or "+rd+", "+rs+", "+rt;
}
static std::string SLT(std::string rd, std::string rs, std::string rt){
    return "slt "+rd+", "+rs+", "+rt;
}
static std::string AND(std::string rd, std::string rs, std::string rt){
    return "and "+rd+", "+rs+", "+rt;
}
static std::string XOR(std::string rd, std::string rs, std::string rt){
    return "xor "+rd+", "+rs+", "+rt;
}

// Imm 2 Par

static std::string LUI(std::string rt, std::string imm){
    return "lui "+rt+", "+imm;
}
static std::string ORI(std::string rt, std::string rs, std::string imm){
    return "ori "+rt+", "+rs+", "+imm;
}
static std::string XORI(std::string rt, std::string rs, std::string imm){
    return "xori "+rt+", "+rs+", "+imm;
}
static std::string ANDI(std::string rt, std::string rs, std::string imm){
    return "andi "+rt+", "+rs+", "+imm;
}
static std::string ADDIU(std::string rt, std::string rs, std::string imm){
    return "addiu "+rt+", "+rs+", "+imm;
}
static std::string SLTIU(std::string rt, std::string rs, std::string imm){
    return "sltiu "+rt+", "+rs+", "+imm;
}

// MEMORY ACCESS

static std::string LW(std::string rt, std::string offset, std::string base){
    return "lw "+rt+", "+offset+"("+base+")";
}
static std::string SW(std::string rt, std::string offset, std::string base){
    return "sw "+rt+", "+offset+"("+base+")";
}

static std::string JR(std::string rs){
    return "jr "+rs;
}
static std::string JAL(std::string LABEL){
    return "jal "+LABEL;
}

static std::string BNE(std::string rs, std::string rt, std::string LABEL){
    return "bne "+rs+", "+rt+", "+LABEL+"\nnop";
}
static std::string BEQ(std::string rs, std::string rt, std::string LABEL){
    return "beq "+rs+", "+rt+", "+LABEL+"\nnop";
}

static std::string MUL(std::string rd, std::string rt, std::string rs){
    return "mul "+rd+", "+rt+", "+rs;
}
static std::string DIV(std::string rs, std::string rt){
    return "div "+rs+", "+rt;
}

static std::string MFHI(std::string rd){
    return "mfhi "+rd;
}
static std::string MFLO(std::string rd){
    return "mflo "+rd;
}

#endif