#include "headers/basics.hpp"
#include "engine.cpp"


char BOARD[SIZE][SIZE] = {};
char PLAYER;
char WIN;
bool DRAW;


void wipe();            
void boardDisplay();    
void displayRules();    
bool checkWin();        
bool checkDraw();       
void end();             
void run();             
void setup();           

///////////////////////////////////////////////////////////////////////////////////////////////////

void wipe() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}


void setup() {
    FOR(i, SIZE) FOR(j, SIZE) BOARD[i][j] = '\0';
    PLAYER = '\0';
    WIN = '\0';
    DRAW = false;
}


void boardDisplay() {
    wipe();
    std::cout << "\033[1;4mGAME STATE\033[0m\n\n";

    FOR(i, SIZE) {
        FOR(u, SIZE) {
            std::cout 
                    << ((u == 0)? " " : "") 
                    << ((BOARD[i][u] == '\0')? ' ' : BOARD[i][u]) 
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
    std::cout << "At any prompt (after turn), input \"R\" to see the rules again.\n";
    std::cout << "At any prompt (after turn), input \"Q\" to end the game.\n";
    std::cout << "Press enter to start game.\n";
    std::cin.get();
    wipe();
}


bool checkWin(char board[SIZE][SIZE]) {
    char winner;
    bool win = false;

    FOR(i, SIZE) {
        if (board[i][0] != '\0' &&
                board[i][0] == board[i][1] &&
                board[i][1] == board[i][2]) {
            winner = board[i][0];
            win = true;
            break;
        }
        if (board[0][i] != '\0' &&
                board[0][i] == board[1][i] &&
                board[1][i] == board[2][i]) {
            winner = board[0][i];
            win = true;
            break;
        }
    }

    if (board[0][0] != '\0' &&
            board[0][0] == board[1][1] &&
            board[1][1] == board[2][2]) {
        winner = board[0][0];
        win = true;
    }

    else if (board[0][2] != '\0' &&
                board[0][2] == board[1][1] &&
                board[1][1] == board[2][0]) {
        winner = board[1][1];
        win = true;
    }

    if (win) WIN = winner;

    return win;
}


bool checkDraw (char board[SIZE][SIZE]) {
    FOR (i, SIZE) FOR(j, SIZE) if (board[i][j] == '\0') return false;

    DRAW = true;
    return true;
}


void end() {
    std::cout << "\n\n\n";
    std::cout << DRAW? "DRAW!\n" : 
                (WIN == PLAYER)? "You win!\n" : "You Lose!\n";
    std::cout << "Press a key to continue:\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void run() {
    displayRules();

    do {
        std::cout << "Please select \"X\" or \"O\": \n";
        PLAYER = std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        bool valid = false;

        switch(PLAYER) {
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
        if (PLAYER == 'X') boardDisplay();
        else {
            makeMove();
            boardDisplay();
            if (checkWin(BOARD) || checkDraw(BOARD)) {
                end();
                break;
            }
        }

        std::pair<int,int> move;
        do {
            std::cout << "\033[1mMake your move:\033[0m\n";
            std::cout << "Row: ";
            while (!(std::cin >> row(move)) || (row(move) < 0 || row(move) >= SIZE)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Input a valid row.\n";
            }

            std::cout << "Column: ";
            while (!(std::cin >> col(move)) || (col(move) < 0 || col(move) >= SIZE)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Input a valid Column.\n";
            }

            if (BOARD[row(move)][col(move)] == '\0') {
                BOARD[row(move)][col(move)] = PLAYER;
            } else {
                std::cout << "This square has been played. Pick another: \n";
                continue;
            }

            break;
        } while (1);

        if (checkWin(BOARD) || checkDraw(BOARD)) {
            boardDisplay();
            end();
            break;
        }
    }
}


int main() {
    do {
        setup();
        run();
        wipe();
        std::cout << "\033[1;4mThanks for playing!\033[0m\n\n";
        std::cout << "\033[4mPress Q to quit, or any other button to play again: \033[0m\n\n";
        std::string again;
        std::cin >> again;
        if (again == "Q") break;
    } while(1);

    wipe();
    std::cout << "\033[1;4mSee you next time!\033[0m\n\n";

    return 0;
}