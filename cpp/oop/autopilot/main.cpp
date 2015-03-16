#include <iostream>
#include "RoadVertex.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    RoadVertex* v = new RoadVertex(0);
    v->setRoadType(INTERSTATE);
    cout << v->getRoadType() << endl;
    return 0;
}
