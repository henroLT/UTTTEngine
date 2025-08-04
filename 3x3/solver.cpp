#include "headers/solver.hpp"


Solver::Solver(const state &init) {
    head = new stateTree(init);
}

Solver::~Solver() {
    delete head;
}

void threadFunc(lfqueue *list, std::unordered_map<state, int> &visit) {
    while(!list->isEmpty()) {
        state temp;
        if (!list->pop(temp)) continue;
        if (visit[temp]) continue;
        visit[temp]++;

        //generate and push children (also check if they in visit, and add them to visit)
        
    }
}

void Solver::generateStates() {
    lfqueue *list = new lfqueue();
    list->push(head->val);
    // spawn threads to generate all game states with helper func
    // use jthreads?
}

std::pair<int,int> Solver::chooseBest() {

}