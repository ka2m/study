#include "Stack.h"

void Stack::push(int item) {
   this->_extend();
   this->_stack[this->_size-1] = item;
}

int Stack::peek() {
    return this->_stack[this->_size-1];
}

int Stack::pop() {
    int item = this->_stack[this->_size-1];
    this->_shrink();
    return item;
}

int Stack::getSize() {
    return this->_size;
}

void Stack::empty() {
    while (this->_size) this->_shrink();
}

void Stack::_extend() {
    this->_size++;
    this->_allocate();
}

void Stack::_shrink() {
    this->_size--;
    this->_allocate();
}

void Stack::_allocate() {
    this->_stack = (int *)realloc(this->_stack,
                                  this->_size * sizeof(int));
}
