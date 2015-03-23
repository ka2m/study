#include "RoadGraph.h"

RoadGraph::RoadGraph(std::string filename) {
    std::ifstream in;
    in.open(filename);
    if (in.is_open()) {
        printf("Reading initial parameters\n");
        int density;
        in >> density;
        float totalDistance;
        in >> totalDistance;
        this->_totalDistance = totalDistance;
        this->_density = density;

        float distance;
        int type, weather, limit;
        in >> distance >> type >> weather >> limit;
        RoadVertex * startv = new RoadVertex(0);
        startv->setDistance(distance);
        startv->setRoadType(type);
        startv->setWeatherCondition(weather);
        startv->setLimit(limit);

        in >> distance >> type >> weather >> limit;

        RoadVertex * endv = new RoadVertex(1);
        endv->setDistance(distance);
        endv->setRoadType(type);
        endv->setWeatherCondition(weather);
        endv->setLimit(limit);

        this->_vertexes.push_back(startv);
        this->_vertexes.push_back(endv);
        printf("Read initial parameters: %d %f\n", density, totalDistance);
    }
}

float RoadGraph::getTotalDistance() {
    return this->_totalDistance;
}

int RoadGraph::getDensity() {
    return this->_density;
}

layerType  RoadGraph::getVertexes() {
    return this->_vertexes;
}

std::map<int, t_vv> RoadGraph::getAdj() {
    return this->_adj;
}

RoadVertex * RoadGraph::getVertexById(int id) {
    for (auto v: this->_vertexes) {
        if (v->getId() == id)
            return v;
    }
    return NULL;
}

void RoadGraph::addLayer(layerType layer, int layerCount) {
    this->_maxLvl = layerCount;
    int previousLevel = --layerCount;
    t_vv ids;
    for (RoadVertex * v: layer) {
       float weight = this->_calculateWeight(v);
       v->setWeight(weight);
       this->_vertexes.push_back(v);
       ids.push_back(v->getId());
    }

    if (!previousLevel) {
        std::cout << "Connecting enter point" << std::endl;
        this->_adj.insert(std::pair<int, t_vv>(0, ids));
    }
    else
    {
        int prevLevelMin = previousLevel * 10;
        int prevLevelMax = previousLevel * 10 + (int) ceil(this->_density / 2) - 1;
        /*for (int v = prevLevelMin; v <= prevLevelMax; v++) {
            ids.push_back(v - 10);
            if (!(v - 10)) break;
        }*/
        printf("Connecting layer with nodes of level %d:  %d - %d\n", previousLevel,  prevLevelMin, prevLevelMax);
        for (int v = prevLevelMin; v <= prevLevelMax; v++) {
            this->_adj.insert(std::pair<int, t_vv>(v, ids));
            }
    }
}

void RoadGraph::addOutro() {
    int newOutroId = (this->_maxLvl + 1) * 10;
    this->getVertexById(1)->setId(newOutroId);
    int prevLevelMin = this->_maxLvl * 10;
    int prevLevelMax = this->_maxLvl * 10 + (int) ceil(this->_density / 2) - 1;
    for (int v = prevLevelMin; v <= prevLevelMax; v++) {
        t_vv outro;
        outro.push_back(newOutroId);
        this->_adj.insert(std::pair<int, t_vv>(v, outro));
    }
}

float RoadGraph::_calculateWeight(RoadVertex * v) {
    float speed = v->getLimit();
    float weatherMultiplier = 1.0;
    switch(v->getWeatherCondition()) {
        case SUN: weatherMultiplier = 0.95; break;
        case RAIN: weatherMultiplier = 0.7; break;
        case SNOW: weatherMultiplier = 0.5; break;
        case HURRICANE: weatherMultiplier = 0.3; break;
    }
    speed = speed * weatherMultiplier;

    float roadMultiplier = 1.0;
    switch(v->getRoadType()) {
        case INTERSTATE: roadMultiplier = 1.3; break;
        case VILLAGE: roadMultiplier = 0.8; break;
        case CITY: roadMultiplier = 0.85; break;
        case MOUNTAIN: roadMultiplier = 0.6; break;
    }
    speed = speed * roadMultiplier;

    float weight = v->getDistance() / speed;
    printf("Calculating ETA for %d\nMax spd: %3.2f\nETA: %2.2f (min)\n",
               v->getId(),
               speed,
               weight * 60);

    return weight;
}
