#include "Stack.h"
#include <cstdio>
using namespace std;

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int size, x, y, tmp;
    cin >> size >> x >> y;

    Stack* s = new Stack();

    for (int i = 0; i < size; i++) {
        cin >> tmp;
        s->push(tmp);
    }

    Stack *result = new Stack();
    while(s->getSize()) {
        int item = s->pop();
        if (item == x) {
            result->push(y);
        }
        result->push(item);
    }
    while(result->getSize()) {
        cout << result->pop() << " ";
    }
    cout << endl;
}
