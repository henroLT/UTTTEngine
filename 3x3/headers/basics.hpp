#pragma once

#include <iostream>
#include <cstdlib>
#include <atomic>
#include <thread>
#include <vector>
#include <unordered_map>
#include <functional>
#include <cstring>

#define FOR(x, n) for (int x = 0; x < n; ++x)
#define SIZE 3
#define row(a) a.first
#define col(a) a.second

extern char BOARD[SIZE][SIZE];
extern char PLAYER;
extern char WIN;
extern bool DRAW;

struct state {
    char board[SIZE][SIZE];
    int player;            
    int turn;

    bool operator==(const state& other) const {
        return player == other.player &&
                turn == other.turn &&
                memcmp(board, other.board, sizeof(board)) == 0;
    }
};

template<>
struct std::hash<state> {
    size_t operator()(const state &s) const {
        size_t h = 0;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                h = h * 31 + s.board[i][j];
            
        h = h * 31 + s.player;
        h = h * 31 + s.turn;
        return h;
    }
};