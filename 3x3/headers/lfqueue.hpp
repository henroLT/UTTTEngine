#pragma once

#include "basics.hpp"
#include "stateTree.hpp"

struct node;
struct pointer;

class lfqueue {
    private:
        std::atomic<pointer> head;
        std::atomic<pointer> tail;

    public:
        lfqueue();
        ~lfqueue();
        void push(stateTree* value);
        bool pop(stateTree*& result);
        bool front(stateTree*& result);
        bool isEmpty();
};


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