#include <iostream>
#include <atomic>
#include <thread>

#define FOR(x, n) for (int x = 0; x < n; ++x)

const int SIZE = 3;
int BOARD[SIZE][SIZE] = {};

struct state {
    int board[SIZE][SIZE];
    int player;            // 1, 2
    int turn;
};

///////////////////////////////////////////////////////////////////////////////////////////////////


void display() {
    FOR(i, SIZE) {
        FOR(u, SIZE) {
            std::cout << ((BOARD[i][u] == 0)? " " : 
                            (BOARD[i][u] == 1)? "X" : 
                                "O")
                                    << " ";
        } std::cout << '\n';
    }
}

int main() {
    display();

    return 0;
}