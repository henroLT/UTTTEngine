#pragma once
#include "../solver.hpp"
#include <fstream>

/*
private:
    int cntMoves(const state &s);
    void threadFunc(lfqueue *list, std::unordered_map<state, stateTree*> &visit, std::mutex &mutt);
    std::vector<stateTree*> generateChildren(stateTree* thingy);
    int eval(const state& s);
    void weighPaths();
public:
    Solver(const state &init);
    ~Solver();
    void generateStates();
    void startWeighPaths();
    std::pair<int,int> chooseBest();
*/


void Solver::threadFunc(lfqueue *list, std::unordered_map<state, stateTree*> &visit) {
    while(true) {
        stateTree *temp;

        if (!list->pop(temp)){
            std::this_thread::yield();
            if (list->isEmpty()) break;
            continue;    
        }

        std::vector<stateTree*> childs = generateChildren(temp);

        for (auto& c : childs) {
            bool seen = true;
            {
                std::lock_guard<std::mutex> lock(mutt);
                if (visit.find(c->val) == visit.end()) {
                    visit[c->val] = c;
                    list->push(c);
                    temp->children.insert(c);
                    c->parents.insert(temp);
                    seen = false;
                }
            }
            if (seen) {
                {
                    std::lock_guard<std::mutex> lock(visit[c->val]->nodeMutt);
                    visit[c->val]->parents.insert(temp);
                }
                {
                    std::lock_guard<std::mutex> lock(temp->nodeMutt);
                    temp->children.insert(visit[c->val]);
                }
                delete c;
            }
        }
    }
}

std::vector<stateTree*> Solver::generateChildren(stateTree* parent) {
    if (eval(parent->val) != -2) return {};
    
    std::vector<stateTree*> res;

    char currentPlayer = (parent->turn % 2 == 0) ? 'X' : 'O';

    for (int i = 0; i < SIZE; ++i) {
        for (int u = 0; u < SIZE; ++u) {
            if (parent->val.board[i][u] == '\0') {
                state a;
                std::memcpy(a.board, parent->val.board, sizeof(a.board));

                a.board[i][u] = currentPlayer;
                stateTree* child = new stateTree(a);
                child->turn = parent->turn + 1;
                res.push_back(child);
            }
        }
    }

    return res;
}

int Solver::eval(const state& s) {
    char (*board)[SIZE] = (char(*)[SIZE]) s.board;

    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] != '\0' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0] != PLAYER ? +1 : -1;
        if (board[0][i] != '\0' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i] != PLAYER ? +1 : -1;
    }


    if (board[0][0] != '\0' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0] != PLAYER ? +1 : -1;

    if (board[0][2] != '\0' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2] != PLAYER ? +1 : -1;

    bool full = true;
    for (int i = 0; i < SIZE && full; ++i)
        for (int j = 0; j < SIZE && full; ++j)
            if (board[i][j] == '\0')
                full = false;

    if (full) return 0;
    
    return -2;
}

void Solver::weighPaths(stateTree* node, std::unordered_map<state, bool>& seen,  std::ofstream* out) {  
    state dummy = node->val;
    if (seen[dummy]) return;
    seen[node->val] = true;

    for (auto& c : node->children) weighPaths(c, seen, out);

    int scr = eval(dummy);
    if (scr != -2) node->score = static_cast<double>(scr);
    else {
        bool compTurn = (node->turn % 2 == 0)? (PLAYER == 'X') : (PLAYER == 'O');
        auto it = node->children.begin();
        node->score = (*it++)->score;
            
        if (compTurn) 
            for (; it != node->children.end(); ++it)
                node->score = std::max(node->score, (*it)->score);

        else 
            for (; it != node->children.end(); ++it)
                node->score = std::min(node->score, (*it)->score);
        
    }

    //// --- Print board and score ---
    //if (out) { // only write if file pointer provided
    //    *out << "Board (turn " << node->turn << "):\n";
    //    for (int i = 0; i < SIZE; ++i) {
    //        for (int j = 0; j < SIZE; ++j) {
    //            char c = node->val.board[i][j];
    //            *out << (c == '\0' ? '.' : c) << ' ';
    //        }
    //        *out << '\n';
    //    }
    //    *out << "Score: " << node->score << "\n\n";
    //}
}



/**********************************  PUBLIC  ************************************* */


Solver::Solver(const state &init) {
    head = new stateTree(init);
    visit[head->val] = head;
}

Solver::~Solver() {
    delete head;
}

void Solver::generateStates() {
    list = new lfqueue();
    list->push(head);

    {
        std::vector<std::jthread> workers;
        for (int i = 0; i < CORES; ++i) {
            workers.emplace_back([this] {
                threadFunc(this->list, visit);
            });
        }
    }

    delete list;
}

void Solver::startWeighPaths(std::unordered_map<state, bool>& seen) {
    std::ofstream file("output.txt");
    weighPaths(head, seen, &file);
    file.close();

}

std::pair<int,int> Solver::chooseBest(const state &s) {
}