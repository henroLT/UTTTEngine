#include "../LFQueue/lfqueue.hpp"

/*
lfqueue();
~lfqueue();
void push(stateTree* value);
bool pop(stateTree*& result);
bool front(stateTree*& result);
bool isEmpty();
*/


lfqueue::lfqueue() {
    node *dummy = new node(nullptr);
    pointer p = {dummy, 0};
    head.store(p);
    tail.store(p);
}

lfqueue::~lfqueue() {
    stateTree *dummy;
    while (pop(dummy));
    delete head.load().ptr;
}

void lfqueue::push(stateTree* value) {
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

bool lfqueue::pop(stateTree *&result) {
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

bool lfqueue::front(stateTree *&result) {
    pointer headOld = head.load();
    pointer next = headOld.ptr->next.load();

    if (headOld.ptr == head.load().ptr) {
        if (next.ptr == nullptr) {
            return false; 
        }
        result = next.ptr->data;
        return true;
    }

    return false;
}

bool lfqueue::isEmpty() {
    stateTree* dummy;
    return !front(dummy);
}