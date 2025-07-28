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

void wipe() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}

void boardDisplay() {
    wipe();
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
    wipe();
    std::cout << "\n\033[1;4mWelcome to Tic-Tac-Toe (3x3)!\033[0m\n\n";
    std::cout << "\033[1mRules:\033[0m\n";
    std::cout << "1. The game is played on a 3x3 grid.\n";
    std::cout << "2. You can choose to be 'X' or 'O'. The system will be the other symbol.\n";
    std::cout << "3. Players take turns placing their marks in empty cells.\n";
    std::cout << "4. To make a move, enter the row and column numbers separated by a space.\n";
    std::cout << "   Rows and columns are numbered from 0 to 2.\n";
    std::cout << "   For example, entering '1,2' marks the cell at row 1, column 2 (0 indexed).\n";
    std::cout << "5. The first player to get three in a row (hor, ver, dia) wins.\n";
    std::cout << "6. If all cells are filled without a winner, the game is a draw.\n\n";
    std::cout << "Good luck and have fun!\n\n";
    std::cout << "At any prompt, input \"R\" to see the rules again.\n";
    std::cout << "At any prompt, input \"Q\" to end the game.\n";
    std::cout << "Press enter to start game.\n";
    std::cin.get();
    wipe();
}

void calculate() {
    // HERES THE GOOD SHENNAGINS
}

void run() {
    displayRules();

    char player;
    do {
        std::cout << "Please select \"X\" or \"O\": \n";
        player = std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        bool valid = false;

        switch(player) {
            case 'Q':
                wipe();
                return;
            case 'R':
                displayRules();
                continue;
            case 'X':
            case 'O':
                valid = true;
                break;
        }
        if (valid) break;

        std::cout << "Invalid input. Please enter \"X\" or \"O\",\n";
    } while (1);

    while (1) {
        if (player == 'X') boardDisplay();
        else {
            calculate();
            boardDisplay();
        }
        
        std::pair<int,int> move;
        do {
            std::cout << "\033[1mMake your move:\033[0m\n";
            std::cout << "Row: \n";
            while (!(std::cin >> move.first) || (move.first < 0 || move.first >= SIZE)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Input a valid row.\n";
            }

            std::cout << "Column: \n";
            while (!(std::cin >> move.second) || (move.second < 0 || move.second >= SIZE)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Input a valid Column.\n";
            }
            
            break;
        } while (1);

    }
}

int main() {
    run();
    wipe();
    std::cout << "\033[1;4mThanks for playing!\033[0m\n\n";
    return 0;
}