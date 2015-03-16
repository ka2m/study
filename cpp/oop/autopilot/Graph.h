#pragma once
#include "RoadVertex.h" 
#include <string>
#include <fstream>
#include <map>

class RoadGraph {
public: 
    RoadGraph(string filename);
    std::vector<RoadVertex> getVertexes();
    std::map<int, std::vector<RoadVertex> > getAdjMap();
private:
   std::vector<RoadVertex> _vertexes();
   std::map<int, std::vector<RoadVertex> > _adj; 
};
