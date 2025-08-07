#pragma once

#include "basics.hpp"
#include "StateTree/stateTree.hpp"
#include "LFQueue/lfqueue.hpp"

class Solver {
    private:
        stateTree *head;
        std::unordered_map<state, stateTree*> visit;
        std::mutex mutt;
        lfqueue *list;

        void threadFunc(lfqueue *list, std::unordered_map<state, stateTree*> &visit, std::mutex &mutt);
        std::vector<stateTree*> generateChildren(stateTree* thingy);

    public:
        Solver(const state &init);
        ~Solver();

        void generateStates();
        std::pair<int,int> chooseBest();
};
