#include "basics.h"

struct node;

typedef struct {
    node* ptr;
    unsigned int count;
} pointer;

struct node {
    state data;
    std::atomic<pointer> next;

    node (const state &s) : data(s) {
        next.store({nullptr, 0});
    }
};

class lfqueue {
    public:
        std::atomic<pointer> head;
        std::atomic<pointer> tail;

        lfqueue() {
            node *dummy = new node({});
            pointer p = {dummy, 0};
            head.store(p);
            tail.store(p);
        }

    private:
        void push() {

        }
        
        bool pop() {

        }

        state front() {

        }
};