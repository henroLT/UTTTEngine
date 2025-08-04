#pragma once

#include "stateTree.hpp"

class Solver {
    private:
        const stateTree *head;
    public:
        Solver(const state &init);
        ~Solver();

        void generateStates();
        std::pair<int,int> chooseBest();
};
