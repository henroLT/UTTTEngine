#include <iostream>
#include <cstdlib>
#include <atomic>
#include <thread>

#define FOR(x, n) for (int x = 0; x < n; ++x)
#define SIZE 3
struct state {
    int board[SIZE][SIZE];
    int player;            // 1, 2
    int turn;
};

int BOARD[SIZE][SIZE] = {};


///////////////////////////////////////////////////////////////////////////////////////////////////


void display() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif

    std::cout << "\033[1;4mGAME STATE\033[0m\n\n";

    FOR(i, SIZE) {
        FOR(u, SIZE) {
            std::cout 
                    << ((u == 0)? " " : "") 
                    << ((BOARD[i][u] == 0)? " " : (BOARD[i][u] == 1)? "X" : "O") 
                    << ((u != SIZE - 1)? " | " : "");
        }
        std::cout << ((i != SIZE - 1)? "\n---+---+---\n" : "\n");
    }
}



void displayRules() {

}

void run() {
    static bool first = true;
    if (first && (first = false)) displayRules();
    

    display();
}

int main() {
    run();

    return 0;
}