#include "../solver.hpp"

/*
private:
    void threadFunc(lfqueue *list, std::unordered_map<state, stateTree*> &visit, std::mutex &mutt);
    std::vector<stateTree*> generateChildren(stateTree* thingy);
    bool isTerminal(const state& s);
public:
    Solver(const state &init);
    ~Solver();
    void generateStates();
    int eval(const state& s);
    void weighPaths();
    std::pair<int,int> chooseBest();
*/



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
            if (visit.find(temp->val) != visit.end()) continue;
            visit[temp->val] = temp;
        }


        std::vector<stateTree*> childs = generateChildren(temp);
        {
            std::lock_guard<std::mutex> lock(mutt);
            for (auto &c : childs) {
                if (visit.find(c->val) == visit.end()) {
                    list->push(c);
                } else delete c;
            }
        }
    }
}

std::vector<stateTree*> Solver::generateChildren(stateTree* thingy) {
    if (isTerminal(thingy->val)) return {};
    
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


/***********************  PUBLIC  ********************************** */


Solver::Solver(const state &init) {
    head = new stateTree(init);
}

Solver::~Solver() {
    delete head;
}

void Solver::generateStates() {
    list = new lfqueue();
    list->push(head);
    
    // For real paralleism with multi core
    // const int numThreads = std::thread::hardware_concurrency();
    const int numThreads = 15;

    {
        std::vector<std::jthread> workers;
        for (int i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                threadFunc(this->list, visit, mutt);
            });
        }
    }
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

void Solver::weighPaths(stateTree* node, const char comp) {  
    if (isTerminal(node->val)) {
        node->score = eval(node->val,comp);
        return;
    }

}

std::pair<int,int> Solver::chooseBest(const state &s) {

}