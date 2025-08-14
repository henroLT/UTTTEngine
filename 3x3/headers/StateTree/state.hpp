#pragma once

#include "../basics.hpp"


struct state {
    char board[SIZE][SIZE];

    state() {
        std::memset(board, '\0', sizeof(board));
    }

    bool operator==(const state& s) const {
        return std::memcmp(board, s.board, sizeof(board));
    }
};

template<>
struct std::hash<state> {
    size_t operator()(const state& s) const {
        size_t h = 0;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                h = h * 31 + static_cast<unsigned char>(s.board[i][j]);
        return h;
    }
};