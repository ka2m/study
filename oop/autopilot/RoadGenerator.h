#pragma once
#include "RoadGraph.h"

struct densityRes {
    int layersCount;
    int nodesPerLayer;
    float avgArcLng;
};

class RoadGenerator {
public:
    RoadGenerator(RoadGraph * graph);
    std::vector<int> getPath();
    RoadGraph * getRoadGraph();
private:
    densityRes _calculateNetwork(int density, float totalDistance);
    RoadGraph * _graph;
};
