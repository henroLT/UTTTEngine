#ifndef BASICS_H
#define BASICS_H

#include <iostream>
#include <cstdlib>
#include <atomic>
#include <thread>

#define FOR(x, n) for (int x = 0; x < n; ++x)
#define SIZE 3
#define row(a) a.first
#define col(a) a.second

struct state {
    char board[SIZE][SIZE];
    int player;            
    int turn;
};

extern char BOARD[SIZE][SIZE];
extern char PLAYER;
extern int WIN;

#endif