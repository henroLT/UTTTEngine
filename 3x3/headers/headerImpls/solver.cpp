#include "../solver.hpp"

/*
private:
    int cntMoves(const state &s);
    void threadFunc(lfqueue *list, std::unordered_map<state, stateTree*> &visit, std::mutex &mutt);
    std::vector<stateTree*> generateChildren(stateTree* thingy);
    bool isTerminal(const state& s);
public:
    Solver(const state &init);
    ~Solver();
    stateTree* getHead();
    void generateStates();
    int eval(const state& s);
    void weighPaths();
    std::pair<int,int> chooseBest();
*/

int Solver::cntMoves(const state &s) {
    int count = 0;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (s.board[i][j] != '\0') ++count;
    return count;
}


void Solver::threadFunc(lfqueue *list, std::unordered_map<state, stateTree*> &visit, std::mutex &mutt) {
    while(true) {
        stateTree *temp;

        if (!list->pop(temp)){
            std::this_thread::yield();
            if (list->isEmpty()) break;
            continue;    
        }

        {
            std::lock_guard<std::mutex> lock(mutt);
            if (visit.find(temp->val) == visit.end()) {
                delete temp;
                return;
            }
            visit[temp->val] = temp;
        }


        std::vector<stateTree*> childs = generateChildren(temp);
        {
            std::lock_guard<std::mutex> lock(mutt);
            for (auto &c : childs) {
                if (visit.find(c->val) == visit.end()) {
                    visit[c->val] = c;
                    list->push(c);
                    temp->children.push_back(c);
                    c->parents.push_back(temp);
                } else {
                    visit[c->val]->parents.push_back(temp);
                    temp->children.push_back(visit[c->val]);
                    delete c;
                }
            }
        }
    }
}

std::vector<stateTree*> Solver::generateChildren(stateTree* thingy) {
    if (isTerminal(thingy->val)) return {};
    
    std::vector<stateTree*> res;

    char currentPlayer = (cntMoves(thingy->val) % 2 == 0) ? 'X' : 'O';

    for (int i = 0; i < SIZE; ++i) {
        for (int u = 0; u < SIZE; ++u) {
            if (thingy->val.board[i][u] == '\0') {
                state a;
                std::memcpy(a.board, thingy->val.board, sizeof(a.board));

                a.board[i][u] = currentPlayer;
                stateTree* child = new stateTree(a);
                res.push_back(child);
            }
        }
    }

    return res;
}

bool Solver::isTerminal(const state& s) {
    char (*board)[SIZE] = (char(*)[SIZE]) s.board;

    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] != '\0' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return true;
        if (board[0][i] != '\0' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return true;
    }

    if (board[0][0] != '\0' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return true;

    if (board[0][2] != '\0' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return true;

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == '\0') return false;

    return true;
}

int Solver::eval(const state& s, const char comp) {
    char (*board)[SIZE] = (char(*)[SIZE]) s.board;

    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] != '\0' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0] == comp ? +1 : -1;
        if (board[0][i] != '\0' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i] == comp ? +1 : -1;
    }


    if (board[0][0] != '\0' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0] == comp ? +1 : -1;

    if (board[0][2] != '\0' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2] == comp ? +1 : -1;

    return 0;

}


/**********************************  PUBLIC  ************************************* */


Solver::Solver(const state &init) {
    head = new stateTree(init);
}

Solver::~Solver() {
    delete head;
}

stateTree* Solver::getHead() {
    return head;
}

void Solver::generateStates() {
    list = new lfqueue();
    list->push(head);

    const int numThreads = coresAvail();

    {
        std::vector<std::jthread> workers;
        for (int i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                threadFunc(this->list, visit, mutt);
            });
        }
    }
    std::cout << visit.size();
    std::cin.get();
}

void Solver::weighPaths(stateTree* node, const char comp, std::unordered_map<state, bool>& seen) {  
    //if (seen[node->val]) return;
    //std::cout << "Weighing turn " << node->val.turn << ", children: " << node->children.size() << "\n";
//
    //for (auto* child : node->children) weighPaths(child, comp, seen);
//
    //if (isTerminal(node->val)) node->score = eval(node->val, comp);
    //else {
    //    char nextPlayer = (node->val.turn % 2 == 0) ? 'X' : 'O';
    //    bool compTurn = (nextPlayer == comp);
//
    //    node->score = compTurn ? INT_MIN : INT_MAX;
//
    //    for (auto* child : node->children) {
    //        if (compTurn) {
    //            node->score = std::max(node->score, child->score);
    //        } else {
    //            node->score = std::min(node->score, child->score);
    //        }
    //    }
//
    //    std::cout << "Internal node score: " << node->score << "\n";
    //}
//
    //seen[node->val] = true;
}

std::pair<int,int> Solver::chooseBest(const state &s, char comp) {
}