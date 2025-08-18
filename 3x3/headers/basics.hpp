#pragma once

#include <iostream>
#include <cstdlib>
#include <atomic>
#include <thread>
#include <vector>
#include <unordered_map>
#include <functional>
#include <cstring>
#include <mutex>
#include <set>
#include <chrono>

#ifdef _WIN32
#else
    #include <unistd.h>
#endif


#define FOR(x, n) for (int x = 0; x < n; ++x)
#define SIZE 3
#define row(a) a.first
#define col(a) a.second
#define INT_MAX 2'147'483'647
#define INT_MIN -2'147'483'648

#ifdef _WIN32
    extern int procs;
    #define CORES procs
#else
    extern long nprocs;
    extern int procs;
    #define CORES procs
#endif

extern char BOARD[SIZE][SIZE];
extern char PLAYER;
extern char WIN;
extern bool DRAW;

bool checkWin(char board[SIZE][SIZE]);
bool checkDraw(char board[SIZE][SIZE]);
void setup();
void wipe(); 
