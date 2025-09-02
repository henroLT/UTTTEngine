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

#define SIZE 9
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


void wipe(); 
void printBoard(char board[SIZE][SIZE]);