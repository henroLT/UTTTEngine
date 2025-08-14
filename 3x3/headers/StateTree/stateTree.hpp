#pragma once

#include "../basics.hpp"
#include "state.hpp"

struct stateTree {
    state val;
    std::vector<stateTree*> parents;
    std::vector<stateTree*> children;
    int score = 0;

    explicit stateTree(const state& s) : val(s) {};
    
};