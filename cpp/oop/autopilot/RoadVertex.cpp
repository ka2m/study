#include "RoadVertex.h"

RoadVertex::RoadVertex(int id, float distance) {
      this->_id = id; 
      this->_distance = distance;
}

void RoadVertex::setRoadType(int type) {
    this->_roadType = type; 
}

void RoadVertex::setWeatherCondition(int condition) {
    this->_weatherCondition = condition; 
}

void RoadVertex::setLimit(int limit) {
    this->_limit = limit; 
}

void RoadVertex::setRandomEvent(int event) {
    this->_randomEvent = event;
}

int RoadVertex::getId() {
    return this->_id;
}

float RoadVertex::getDistance() {
    return this->_distance;
}

int RoadVertex::getRoadType() {
    return this->_roadType;
}

int RoadVertex::getWeatherCondition() {
    return this->_weatherCondition;
}

int RoadVertex::getLimit() {
    return this->_limit;
}

int RoadVertex::getRandomEvent() {
    return this->_randomEvent;
}
