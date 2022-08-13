#ifndef ast_hpp
#define ast_hpp

#include <string>
#include <iostream>
#include <vector>

#include "ast_context.hpp"
#include "instruction_formats.hpp"
#include "ast/ast_base.hpp"
#include "ast/ast_values.hpp"
#include "ast/ast_unary.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_increment.hpp"
#include "ast/ast_functioncall.hpp"
#include "ast/ast_eval.hpp"
#include "ast/ast_parseq.hpp"
#include "ast/ast_arraywrite.hpp"
#include "ast/ast_arrayread.hpp"
#include "ast/ast_arrayseq.hpp"
#include "ast/ast_arraydef.hpp"
#include "ast/ast_argseq.hpp"
#include "ast/ast_declare.hpp"
#include "ast/ast_breakcont.hpp"
#include "ast/ast_return.hpp"
#include "ast/ast_line.hpp"
#include "ast/ast_if.hpp"
#include "ast/ast_while.hpp"
#include "ast/ast_for.hpp"
#include "ast/ast_case.hpp"
#include "ast/ast_caseseq.hpp"
#include "ast/ast_switch.hpp"
#include "ast/ast_seq.hpp"
#include "ast/ast_nocomfunctions.hpp"
#include "ast/ast_blockdec.hpp"
#include "ast/ast_blockseq.hpp"

extern const Base *parseAST(std::string inputFile);

#endif
