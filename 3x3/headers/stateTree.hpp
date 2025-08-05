#pragma once

#include "lfqueue.hpp"

struct stateTree {
    state val;
    stateTree *parent;
    std::vector<stateTree*> children;

    stateTree(const state &value, stateTree *parentNode = nullptr) : 
        val(value), parent(parentNode){}

    ~stateTree() {
        for (stateTree* child : children) {
            delete child;
        }
    }
};

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