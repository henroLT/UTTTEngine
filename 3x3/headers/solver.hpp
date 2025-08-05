#pragma once

#include "stateTree.hpp"

class Solver {
    private:
        stateTree *head;
        std::unordered_map<stateTree*, int> visit;
        std::mutex mutt;
        lfqueue *list;

        void threadFunc(lfqueue *list, std::unordered_map<stateTree*, int> &visit, std::mutex &mutt);
        std::vector<stateTree*> generateChildren(stateTree* thingy);

    public:
        Solver(const state &init);
        ~Solver();

        void generateStates();
        std::pair<int,int> chooseBest();
};
