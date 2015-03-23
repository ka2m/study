#pragma once
#include <map>
#include <sstream>
#include <string>
enum ROAD_TYPE { UNDEFINED, INTERSTATE, VILLAGE, CITY, MOUNTAIN };
enum WEATHER_CONDITION { NORMAL, SUN, RAIN, SNOW, HURRICANE };
enum RANDOM_EVENT { NONE, CAR_BROKEN, TRAFFIC, POLICE, CAR_ON_THE_ROAD };


class RoadVertex {
public:
    RoadVertex(int id);
    RoadVertex(int id, float distance);

    void setId(int id);
    void setDistance(float distance);
    void setRoadType(int type);
    void setWeatherCondition(int condition);
    void setLimit(int limit);
    void setRandomEvent(int event);
    void setWeight(float weight);

    int getId();
    float getDistance();
    int getRoadType();
    int getWeatherCondition();
    int getLimit();
    int getRandomEvent();
    float getWeight();

    std::string toString();
private:
    int _id;
    float _distance;
    int _roadType;
    int _weatherCondition;
    int _limit;
    int _randomEvent;
    float _weight;
};

