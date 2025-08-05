#include "headers/solver.hpp"


Solver::Solver(const state &init) {
    head = new stateTree(init);
}

Solver::~Solver() {
    delete head;
}

void threadFunc(lfqueue *list, std::unordered_map<stateTree*, int> &visit, std::mutex &mutt) {
    while(!list->isEmpty()) {
        stateTree *temp;
        if (!list->pop(temp)) continue;
        {
            std::lock_guard<std::mutex> lock(mutt);
            if (visit[temp]++) continue;
        }

        std::vector<stateTree*> childs = generateChildren(temp);
        
        for (auto &c : childs) {
            std::lock_guard<std::mutex> lock(mutt);
            if (!visit[c]++) list->push(c);
        }
    }
}

//struct state {
//    char board[SIZE][SIZE];
//    int player;            
//    int turn;

std::vector<stateTree*> generateChildren(stateTree* thingy) {
    std::vector<stateTree*> res;

    for (int i = 0; i < SIZE; ++i) {
        for (int u = 0; u < )
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