#include "RoadGenerator.h"

int main() {
    RoadGraph * graph = new RoadGraph("data");
    RoadGenerator * generator = new RoadGenerator(graph);
    std::cout << "------------\n";
    std::vector<int> path = generator->getPath();
    std::cout<< "Path: ";
    for (std::vector<int>::iterator it = path.begin(); it != path.end(); ++it) {
        std::cout << *it;
        if (it + 1 != path.end()) std::cout << "->";
    }
    std::cout << std::endl;
    return 0;
}
