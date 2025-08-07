#pragma once

#include "../basics.hpp"

struct state {
    char board[SIZE][SIZE];           
    int turn;

    bool operator==(const state& other) const {
        return turn == other.turn &&
                memcmp(board, other.board, sizeof(board)) == 0;
    }
};

template<>
struct std::hash<state> {
    size_t operator()(const state &s) const {
        size_t h = 0;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                h = h * 31 + static_cast<unsigned char>(s.board[i][j]);
            
        h = h * 31 + s.turn;
        return h;
    }
};