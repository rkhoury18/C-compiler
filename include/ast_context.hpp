#ifndef ast_context_hpp
#define ast_context_hpp

#include "ast.hpp"
#include <string>
#include<iostream>
#include <vector>

struct context {

    int makeNameUnq = 0;
    std::vector<std::vector<std::pair<std::string, int>>> stackScope; // 2D List Of PAIRS (var name, spoffset)
    std::vector<int> scopeOffsets;
    std::vector<std::string> currentFunc;
    int offset = 0;
    std::vector<std::string> BreakTracker;
    std::vector<std::string> LoopTracker;
    int counter = 0;
    int parMaxSize = 0;
    int counter2 = 0;
    
};

#endif