#include "Queue.h"

void Queue::push(int item) {
   if (!this->_size) {
        this->_queue = (int *)malloc(0);
        this->_size++;
   }
   else {
       this->_size++;
       this->_queue = (int *)realloc(this->_queue,
                                     this->_size * sizeof(int));
   }
   this->_queue[this->_size-1] = item;
}

int Queue::peek() {
    if (this->_size)
        return this->_queue[0];
    return NULL;
}

int Queue::pop() {
    int item;
    if (this->_size) {
        item = this->_queue[0];
    }
    else
        return NULL;
    this->_size--;
    this->_queue++;
    return item;
}

int Queue::tail() {
    return this->_queue[this->_size-1];
}

int Queue::getSize() {
    return this->_size;
}
