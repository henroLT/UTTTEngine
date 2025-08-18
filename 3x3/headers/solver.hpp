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

        void threadFunc(lfqueue *list, std::unordered_map<state, stateTree*> &visit);
        std::vector<stateTree*> generateChildren(stateTree* thingy);
        int eval(const state& s);
        
    public:
        Solver(const state &init);
        ~Solver();
        void weighPaths(stateTree* node, std::unordered_map<state, bool>& seen,  std::ofstream* out);
        void generateStates();
        void startWeighPaths(std::unordered_map<state, bool>& seen);
        void chooseBest();
};
