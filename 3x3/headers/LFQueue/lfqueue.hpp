#pragma once

#include "../basics.hpp"
#include "lfQueueStructs.hpp"
#include "../StateTree/stateTree.hpp"

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