#pragma once

#include "../basics.hpp"
#include "stateTreeStructs.hpp"

struct stateTree {
    state val;
    std::vector<stateTree*> parents;
    std::vector<stateTree*> children;
    int score = 0;

    explicit stateTree(const state &v) :
        val(v), score(0) {};

};