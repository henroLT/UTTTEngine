#include "../basics.hpp"


#ifdef _WIN32
    int procs =  = static_cast<int>(std::thread::hardware_concurrency());
#else
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    int procs = (nprocs > 0)? static_cast<int>(nprocs) : 1;
#endif



void wipe() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}


void printBoard(char board[SIZE][SIZE]) {
    for (int bigRow = 0; bigRow < 3; ++bigRow) {
        for (int smallRow = 0; smallRow < 3; ++smallRow) {
            for (int bigCol = 0; bigCol < 3; ++bigCol) {
                for (int smallCol = 0; smallCol < 3; ++smallCol) {
                    int row = bigRow * 3 + smallRow;
                    int col = bigCol * 3 + smallCol;
                    char cell = board[row][col];
                    std::cout << (cell == '\0' ? '.' : cell) << ' ';
                }
                if (bigCol < 2) std::cout << "| ";
            }
            std::cout << "\n";
        }
        if (bigRow < 2) std::cout << "------+-------+------\n";
    }
}