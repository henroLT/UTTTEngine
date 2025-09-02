#include "../solver.hpp"

/*
private:
    void threadFunc(lfqueue *list, std::unordered_map<state, stateTree*> &visit);
    std::vector<stateTree*> generateChildren(stateTree* thingy);
    int eval(const state& s);
    void weighPaths(stateTree* node, std::unordered_map<state, bool>& seen);
public:
    Solver(const state &init);
    ~Solver();
    void generateStates();
    void startWeighPaths(std::unordered_map<state, bool>& seen);
    void chooseBest();
*/


void Solver::threadFunc(lfqueue *list, std::unordered_map<state, stateTree*> &visit) {
    while(true) {
        stateTree *temp;

        if (!list->pop(temp)){
            std::this_thread::yield();
            if (list->isEmpty()) break;
            if (visit.size() == 5478) break;
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
                    seen = false;
                }
            }
            if (seen) {
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

void Solver::weighPaths(stateTree* node, std::unordered_map<state, bool>& seen) {  
    if (seen[node->val]) return;
    state dummy = node->val;
    seen[node->val] = true;

    for (auto& c : node->children) weighPaths(c, seen);

    int scr = eval(dummy);
    if (scr != -2) node->score = static_cast<double>(scr);
    else {
        double sum = 0.0;
        double numChild = static_cast<double>(node->children.size());
        for (const auto& c : node->children) sum += c->score;

        node->score = sum / numChild;
    }
}



/**********************************  PUBLIC  ************************************* */


Solver::Solver(const state &init) {
    head = new stateTree(init);
    visit[head->val] = head;
}

Solver::~Solver() {
    for (auto it = visit.begin(); it != visit.end(); ) {
        delete it->second;
        it = visit.erase(it);
    }
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
    weighPaths(head, seen);
}

void Solver::chooseBest() {
    // find the best move (highest rated)
    state temp(BOARD);
    state best = (*(visit[temp]->children.begin()))->val;
    for (const auto& c : visit[temp]->children)
        if (visit[best]->score < c->score)
            best = c->val;
    
    memcpy(BOARD, best.board, sizeof(BOARD));
}