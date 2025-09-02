#include "../headers/basics.hpp"

char BOARD[SIZE][SIZE] = {};
char PLAYER;
char WIN;
bool DRAW;

void rules() {
    std::cout << "\033[1;4mWelcome to Ultimate Tic Tac Toe!\033[0m\n\n";
    std::cout << "Rules:\n";
    std::cout << "1. The game is played on a 3x3 grid of Tic Tac Toe boards (making a 9x9 board).\n";
    std::cout << "2. Players take turns placing their mark (X or O) on the small boards.\n";
    std::cout << "3. The twist: the move you make in a small board determines which small board your opponent plays in next.\n";
    std::cout << "     For example, if you place your mark in the top-right cell of a small board,\n";
    std::cout << "     your opponent must play in the top-right small board on their turn.\n";
    std::cout << "4. If a small board is already won or full, the next player can play anywhere.\n";
    std::cout << "5. Win a small board by getting three in a row (horizontally, vertically, or diagonally).\n";
    std::cout << "6. Win the game by winning three small boards in a row on the big 3x3 grid.\n";
    std::cout << "7. If all boards are full and no player has three small boards in a row, the game is a draw.\n\n";
    std::cout << "Below is an example board\n\n";
    printBoard(BOARD);
    std::cout << "\n\n\033[1;4mPress enter to begin.\033[0m\n";
    std::cin.get();
}


bool exitLoop() {
    wipe();
    std::string temp;
    do {
        std::cout << "Enter Q to exit, R to play again.\n";
        std::cin >> temp;
    } while (temp != "Q" && temp != "R");

    return (temp == "Q")? true : false;
}

int main() {
    do {
        rules();

    } while(!exitLoop());


    std::cout << "\033[1;4mBye! Thanks for playing.\033[0m\n\n";
}