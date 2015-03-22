#include "RoadGenerator.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cfloat>

RoadGenerator::RoadGenerator(RoadGraph * graph) {
    this->_graph = graph;
    densityRes dr = this->_calculateNetwork(this->_graph->getDensity(),
                                            this->_graph->getTotalDistance());

    printf("\nCreating random roads\nLayers: %d\nNodes per layer: %d\nAverage road length (+/- 1 km): %2.1f\n",
             dr.layersCount, dr.nodesPerLayer, dr.avgArcLng);

    srand(time(NULL));

    for(int layer = 0; layer < dr.layersCount; layer++) {
        int layerId = (layer + 1) * 10;
        std::vector<RoadVertex *> _layer;
        for (int node = 0; node < dr.nodesPerLayer; node++) {
            int id = layerId + node;
            float length = dr.avgArcLng + ((float)(rand() % 200 - 100) / 100.0);
            int roadType = rand() % 5;
            int limit = 55;
            switch(roadType) {
                case INTERSTATE: limit = 120; break;
                case VILLAGE: limit = 50; break;
                case CITY: limit = 60; break;
                case MOUNTAIN: limit = 70; break;
            }
            int weather  = rand() % 5;
            RoadVertex * v = new RoadVertex(id, length);
            v->setRoadType(roadType);
            v->setWeatherCondition(weather);
            v->setLimit(limit);
            std::cout << v->toString();
            _layer.push_back(v);
        }
        this->_graph->addLayer(_layer, layer + 1);
        std::cout << "Layer added" << std::endl << std::endl;
    }
    this->_graph->addOutro();
}


std::vector<int> RoadGenerator::getPath() {
    std::vector<int> result;
    std::map<int, t_vv> __adj = this->_graph->getAdj();

    std::cout << "Finding best path" << std::endl;

    /*for (auto p: __adj)
    {
        std::cout << p.first << ": ";
        for (auto pp: p.second)
            std::cout << pp << " ";
        std::cout << std::endl;
    }*/
    float total_path = 0;
    float total_time = 0;
    bool  hasStarted = false;
    int _id = -1;
    for (auto p: __adj)  {
        if (hasStarted && p.first != _id) continue;
        hasStarted = true;
        float _time = FLT_MAX;
        for (auto pp: p.second) {
            float w = this->_graph->getVertexById(pp)->getWeight();
            if (w < _time) {
                _time = w;
                _id = this->_graph->getVertexById(pp)->getId();
            }
        }
        float d = this->_graph->getVertexById(_id)->getDistance();
        //printf("%d(%2.1f)->", _id, d);
        total_time += _time;
        total_path += d;
        result.push_back(_id);
    }
    printf("\nCompleted %f km in %f h\n", total_path, total_time);

    return result;
}


densityRes RoadGenerator::_calculateNetwork(int density, float totalDistance) {
    densityRes res;
    res.layersCount = density;
    res.nodesPerLayer = (int) ceil(density / 2);
    res.avgArcLng = (float) round(totalDistance / density);
    return res;
}
