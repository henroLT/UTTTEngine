#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "lfqueue.hpp"

struct stateTree {
    state val;
    stateTree *parent;
    std::vector<stateTree> children;
};

void calculate();
void generateTree();
void traceUp();
void makeMove();



#endif