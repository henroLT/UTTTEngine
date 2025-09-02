#include "../headers/basics.hpp"

char BOARD[SIZE][SIZE] = {};
char PLAYER;
char WIN;
bool DRAW;

void rules() {
    std::cout << "\033[1;4mWelcome to Ultimate Tic Tac Toe!\033[0m\n";
}

bool exitLoop() {
    wipe();
    string temp;
    do {
        std::cout << "Enter Q to exit, R to play again.\n";
        cin >> temp;
    } while (temp != "Q" || temp != "R");

    return (temp == "Q")? true : false;
}

int main() {
    do {
        rules();
        
    } while(exitLoop());


    std::cout << "\033[1;4mBye! Thanks for playing.\033[0m\n";
}