#pragma once

#include "../basics.hpp"
#include "state.hpp"

struct stateTree {
    state val;
    std::set<stateTree*> parents;
    std::set<stateTree*> children;
    int score = 0;
    std::mutex nodeMutt;

    explicit stateTree(const state& s) : val(s) {};

};