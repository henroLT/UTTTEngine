#pragma once

#include "basics.hpp"

struct node;
struct pointer;

class lfqueue {
    private:
        std::atomic<pointer> head;
        std::atomic<pointer> tail;

    public:
        lfqueue();
        ~lfqueue();
        void push(const state &value);
        bool pop(state &result);
        bool front(state &result);
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
    state data;
    std::atomic<pointer> next;

    node (const state &s) : data(s) {
        next.store({nullptr, 0});
    }
};