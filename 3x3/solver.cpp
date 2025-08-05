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
        {
            std::lock_guard<std::mutex> lock(mutt);
            for (auto &c : childs) {
            
                if (!visit[c]++) list->push(c);
            }
        }
    }
}

std::vector<stateTree*> generateChildren(stateTree* thingy) {
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
    list->push(head->val);
    // spawn threads to generate all game states with helper func
    // use jthreads?
}

std::pair<int,int> Solver::chooseBest() {

}