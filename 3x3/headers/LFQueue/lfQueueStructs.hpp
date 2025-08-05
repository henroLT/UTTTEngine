#pragma once

#include "../basics.hpp"
#include "../StateTree/stateTree.hpp"

struct node;
struct pointer;
struct state;

struct pointer {
    node* ptr;
    unsigned int count;

    bool operator==(const pointer &other) const {
        return ptr == other.ptr && count == other.count;
    }
};

struct node {
    stateTree* data;
    std::atomic<pointer> next;

    node (stateTree* s) : data(s) {
        next.store({nullptr, 0});
    }
};
