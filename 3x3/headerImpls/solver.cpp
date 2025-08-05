#include "headers/solver.hpp"


Solver::Solver(const state &init) {
    head = new stateTree(init);
}

Solver::~Solver() {
    delete head;
}

void Solver::threadFunc(lfqueue *list, std::unordered_map<stateTree*, int> &visit, std::mutex &mutt) {
    while(!list->isEmpty()) {
        stateTree *temp;

        if (!list->pop(temp)) continue;
        {
            std::lock_guard<std::mutex> lock(mutt);
            if (visit[temp]++) continue;
        }

        std::vector<stateTree*> childs = generateChildren(temp);
        {
            std::lock_guard<std::mutex> lock(mutt);
            for (auto &c : childs) {
            
                if (!visit[c]++) list->push(c);
            }
        }
    }
}

std::vector<stateTree*> Solver::generateChildren(stateTree* thingy) {
    std::vector<stateTree*> res;

    char board[SIZE][SIZE];
    std::memcpy(board, thingy->val.board, sizeof(board));
    char currentPlayer = (thingy->val.turn % 2 == 1) ? 'X' : 'O';

    for (int i = 0; i < SIZE; ++i) {
        for (int u = 0; u < SIZE; ++u) {
            if (board[i][u] == '\0') {
                state a;
                std::memcpy(a.board, board, sizeof(a.board));

                a.board[i][u] = currentPlayer;
                a.turn = thingy->val.turn + 1;

                stateTree* child = new stateTree(a, thingy);
                res.push_back(child);
            }
        }
    }

    return res;
}

void Solver::generateStates() {
    lfqueue *list = new lfqueue();
    list->push(head);
    
    // For real paralleism with multi core
    // const int numThreads = std::thread::hardware_concurrency();
    const int numThreads = 15;
    std::vector<std::jthread> workers;

    for (int i = 0; i < numThreads; ++i) {
        workers.emplace_back([list, this] {
            threadFunc(list, visit, mutt);
        });
    }
}

std::pair<int,int> Solver::chooseBest() {

}