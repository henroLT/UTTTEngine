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

        int cntMoves(const state &s);
        void threadFunc(lfqueue *list, std::unordered_map<state, stateTree*> &visit);
        std::vector<stateTree*> generateChildren(stateTree* thingy);
        bool isTerminal(const state& s);
        int eval(const state& s, char comp);
    public:
        Solver(const state &init);
        ~Solver();
        stateTree* getHead();
        void generateStates();
        void weighPaths(stateTree* node, const char comp, std::unordered_map<state, bool>& seen);
        std::pair<int,int> chooseBest(const state &s, char comp);
};
