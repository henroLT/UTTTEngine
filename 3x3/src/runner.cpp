#include "../headers/basics.hpp"
#include "../headers/solver.hpp"


char BOARD[SIZE][SIZE] = {};
char PLAYER;
char WIN;
bool DRAW;
Solver *solver;

            
void boardDisplay();    
void displayRules();           
void end();             
void run();                       

///////////////////////////////////////////////////////////////////////////////////////////////////

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

void end() {
    std::cout << "\n\n\n";
    std::cout << ((DRAW)? "DRAW!\n" : 
                (WIN == PLAYER)? "You win!\n" : "You Lose!\n");
    std::cout << "Press enter to continue:\n";
    std::cin.get();
}


void run(bool& weighedPaths) {
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

    if (!weighedPaths) {
        std::unordered_map<state, bool> dummyVisit;
        solver->weighPaths(solver->getHead(), PLAYER, dummyVisit);
        weighedPaths = true;
        std::cout << solver->getHead()->children[1]->score;
        std::cin.get();
    }

    while (1) {
        boardDisplay();

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

        // HERE WE CHOOSE MOVE FROM SOLVER CLASS

        if (checkWin(BOARD) || checkDraw(BOARD)) {
            boardDisplay();
            end();
            break;
        }
    }
}


int main() {
    state begin;
    solver = new Solver(begin);
    solver->generateStates();
    
    bool pathsWeighed = false;

    do {
        setup();
        run(pathsWeighed);
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