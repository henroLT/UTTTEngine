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
        bool isTerminal(const state& s);
    public:
        Solver(const state &init);
        ~Solver();
        void generateStates();
        int eval(const state& s, char comp);
        void weighPaths(stateTree* node, const char comp);
        std::pair<int,int> chooseBest(const state &s);
};
