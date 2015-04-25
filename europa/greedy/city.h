/*
 * city.h
 *
 *  Created on: 06/04/2015
 *      Author: Bruno
 */

#ifndef CITY_H_
#define CITY_H_

#include <string>

class City{
public:
    std::string name;
    std::string info;
    double preference;
    double visitTime;
    double mostExpensiveArrivalRoute;
    
    
    City(std::string name, std::string info, double preference, double visitTime, double mostExpensiveArrivalRoute):
    name(name),info(info),preference(preference),visitTime(visitTime),mostExpensiveArrivalRoute(mostExpensiveArrivalRoute)
    {}
    
    City(){};
    
    double getPreference()
    { return preference;}
    double getMaxPossibleTravelTimeSpent()
    { return visitTime+mostExpensiveArrivalRoute;}
    double getMaxPossibleTravelTimeSpentOnStart()
    { return mostExpensiveArrivalRoute*2;}
};

    
    
#endif /* CITY_H_ */
