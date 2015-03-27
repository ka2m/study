#pragma once
#include "RoadVertex.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cfloat>

typedef std::vector<RoadVertex *> layerType;
typedef std::vector<int> t_vv;

class RoadGraph {
public:
    RoadGraph(std::string filename);

    layerType getVertexes();
    std::map<int, t_vv> getAdj();

    float getTotalDistance();
    int getDensity();
    RoadVertex * getVertexById(int id);

    void addOutro();
    void addLayer(layerType layer, int layerCount);
private:
    layerType _vertexes;
    int _maxLvl;
    float _totalDistance;
    int _density;
    float _calculateWeight(RoadVertex * v);
    std::map<int, t_vv> _adj;
};
