#include "Queue.h"
#include <cstdio>
#include <climits>
using namespace std;

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int size;
    cin >> size;

    Queue* q = new Queue();
    Queue* res = new Queue();

    for (int i = 0; i < size; i++) {
        int tmp;
        cin >> tmp;
        q->push(tmp);
    }
    int min = INT_MAX;
    int max = INT_MIN;
    while (q->getSize()) {
        int item = q->pop();
        if (item > max) max = item;
        else if (item < min) min = item;
        res->push(item);
    }

    while (res->getSize()) {
        int item = res->pop();
        if (item == min) q->push(max);
        else if (item == max) q->push(min);
        else q->push(item);
    }

    while (q->getSize()) {
        cout << q->pop() << " ";
    }
    cout << endl;
}
