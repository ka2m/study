#include <iostream>
#include <cstdlib>

class Queue {
private:
    int* _queue;
    int _size;
public:
    Queue() {
        this->_size = 0;
        this->_queue = (int *)malloc(0);
        }
    ~Queue() { }
    void push(int item);
    int peek();
    int tail();
    int pop();
    int getSize();
};
