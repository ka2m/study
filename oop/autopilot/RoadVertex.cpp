#include "RoadVertex.h"
#include <iostream>

RoadVertex::RoadVertex(int id) {
    this->_id = id;
    this->_randomEvent = NONE;
}

RoadVertex::RoadVertex(int id, float distance) {
    this->_id = id;
    this->_distance = distance;
    this->_randomEvent = NONE;
}

void RoadVertex::setId(int id) {
    this->_id = id;
}

void RoadVertex::setDistance(float distance) {
    this->_distance = distance;
}

void RoadVertex::setWeight(float weight) {
    this->_weight = weight;
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

float RoadVertex::getWeight() {
    return this->_weight;
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

std::string RoadVertex::toString() {
    std::stringstream s;
    if (!this->_id) {
        s << "EntryPoint ";
    }
    else if (this->_id == 1) {
        s << "Destination ";
    }
    else
        s << "RoadVertex ";
    s << "(#/T/D/L/W/E): "  << this->_id << " ";
    s << this->_distance << " ";
    switch(this->_roadType) {
        case UNDEFINED: s << "UNDEFINED"; break;
        case INTERSTATE: s << "INTERSTATE"; break;
        case VILLAGE: s <<  "VILLAGE"; break;
        case CITY: s <<  "CITY"; break;
        case MOUNTAIN: s << "MOUNTAIN"; break;
    }
    s << " ";
    s << this->_limit << " ";
    switch(this->_weatherCondition) {
        case NORMAL: s << "NORMAL"; break;
        case SUN: s << "SUN"; break;
        case RAIN: s << "RAIN"; break;
        case SNOW: s << "SNOW"; break;
        case HURRICANE: s << "HURRICANE"; break;
    }
    s << " ";
    switch(this->_randomEvent) {
        case NONE: s << "NONE"; break;
        case CAR_BROKEN: s << "CAR_BROKEN"; break;
        case TRAFFIC: s << "TRAFFIC"; break;
        case POLICE: s << "POLICE"; break;
        case CAR_ON_THE_ROAD: s << "CAR_ON_THE_ROAD"; break;
    }
    s << std::endl;
    return s.str();

}
