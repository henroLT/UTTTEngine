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

#ifdef _WIN32
#else
    #include <unistd.h>
#endif

#define FOR(x, n) for (int x = 0; x < n; ++x)
#define SIZE 3
#define row(a) a.first
#define col(a) a.second

extern char BOARD[SIZE][SIZE];
extern char PLAYER;
extern char WIN;
extern bool DRAW;

bool checkWin(const char board[SIZE][SIZE]);
bool checkDraw(const char board[SIZE][SIZE]);
void setup();
void wipe(); 
int coresAvail();
