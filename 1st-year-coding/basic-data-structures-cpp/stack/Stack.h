#include <iostream>
#include <cstdlib>

class Stack {
private:
    int* _stack;
    int _size;
public:
    Stack() {
        this->_size = 0;
        this->_stack = (int *)malloc(0);
        }
    ~Stack() { this->empty(); }
    void push(int item);

    int peek();
    int pop();
    int getSize();

    void empty();
private:
    void _extend();
    void _shrink();
    void _allocate();
};
