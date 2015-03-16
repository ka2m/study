#pragma once
#include <map>
enum ROAD_TYPE { UNDEFINED, INTERSTATE, VILLAGE, CITY, MOUNTAIN };
enum WEATHER_CONDITION { NORMAL, SUN, RAIN, SNOW, HURRICANE };
enum RANDOM_EVENT { NONE, CAR_BROKEN, TRAFFIC, POLICE, CAR_ON_THE_ROAD };


class RoadVertex {
public:
    RoadVertex(int id, float distance);

    void setRoadType(int type);
    void setWeatherCondition(int condition);
    void setLimit(int limit);
    void setRandomEvent(int event);
   
    int getId();
    float getDistance();
    int getRoadType();
    int getWeatherCondition();
    int getLimit();
    int getRandomEvent();
private:
    int _id;
    float _distance;
    int _roadType;
    int _weatherCondition;
    int _limit;
    int _randomEvent;
};

