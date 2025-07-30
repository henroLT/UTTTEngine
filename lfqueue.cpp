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
        void push(const state &value) {
            node* newNode = new node(value);
            pointer tailOld;

            while (true) {
                tailOld = tail.load();
                pointer next = tailOld.ptr->next.load();

                if (tailOld.ptr == tail.load().ptr) {
                    if (next.ptr == nullptr) {
                        pointer newNext = {newNode, next.count + 1};
                        if (tailOld.ptr->next.compare_exchange_weak(next, newNext)) {
                            pointer newTail = {newNode, tailOld.count + 1};
                            tail.compare_exchange_strong(tailOld, newTail);
                            return;
                        }
                    } else {
                        pointer newTail = {next.ptr, tailOld.count + 1};
                        tail.compare_exchange_strong(tailOld, newTail);
                    }
                }
            }
        }
        
        bool pop(state &result) {
            pointer headOld;

            while (true) {
                headOld = head.load();
                pointer tailOld = tail.load();
                pointer next = headOld.ptr->next.load();

                if (headOld.ptr == head.load().ptr) {
                    if (headOld.ptr == tailOld.ptr) {
                        if (next.ptr == nullptr) {
                            return false;
                        }
                        pointer newTail = {next.ptr, tailOld.count + 1};
                        tail.compare_exchange_strong(tailOld, newTail);
                    } else {
                        result = next.ptr->data;
                        pointer newHead = {next.ptr, headOld.count + 1};
                        if (head.compare_exchange_strong(headOld, newHead)) {
                            delete headOld.ptr;
                            return true;
                        }
                    }
                }
            }  
        }

        bool front(state &result) {
            pointer headOld = head.load();
            pointer next = headOld.ptr->next.load();

            if (next.ptr == nullptr) {
                return false; 
            }
            result = next.ptr->data;
            return true;
        }

        ~lfqueue() {
            state dummy;
            while (pop(dummy));
            delete head.load().ptr;
        }
};