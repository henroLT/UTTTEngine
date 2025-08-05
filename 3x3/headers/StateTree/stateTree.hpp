#pragma once

#include "../basics.hpp"
#include "stateTreeStructs.hpp"

struct stateTree {
    state val;
    stateTree *parent;
    std::vector<stateTree*> children;

    stateTree(const state &value, stateTree *parentNode = nullptr) : 
        val(value), parent(parentNode){}

    ~stateTree() {
        for (stateTree* child : children) {
            delete child;
        }
    }
};