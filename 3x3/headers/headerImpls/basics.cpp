#include "../basics.hpp"

/*
bool checkWin(const char board[SIZE][SIZE]);
bool checkDraw(const char board[SIZE][SIZE]);
void setup();
void wipe();
*/

#ifdef _WIN32
    int procs =  = static_cast<int>(std::thread::hardware_concurrency());
#else
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    int procs = (nprocs > 0)? static_cast<int>(nprocs) : 1;
#endif


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