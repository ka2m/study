#include "RoadGraph.h"

RoadGraph::RoadGraph(string filename) {
    std::ifstream in;
    in.open(filename);
    if (in.is_open()) {
        int density;
        in >> density;
        float totalDistance;
        in >> totalDistance;

        std::string str;
        getline(in, str);
        std::stringstream s(str);

        float distance;
        int type, weather, limit;
        s >> distance >> type >> weather >> limit;
        RoadVertex* startv = RoadVertex(0, distance);
        startv->setRoadType(type);
        startv->setWeatherCondition(weather);
        startv->setLimit(limit);

        getline(in, str);
        std::stringstream end(str);
        end >> distance, type >> weather >> limit;

        RoadVertex* endv = RoadVertex(0, distance);
        endv->setRoadType(type);
        endv->setWeatherCondition(weather);
        endv->setLimit(limit);


    }
}
