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
    int x,y;
    double preference;
    double visitTime;
    double mostExpensiveArrivalRoute;
    int index;//index in the original edge vector, -1 if not selected
    //bool selected;
    
    City(std::string name, std::string info, double preference, double visitTime, double mostExpensiveArrivalRoute,int x=0,int y=0):
    name(name),x(x),y(y),info(info),preference(preference),visitTime(visitTime),mostExpensiveArrivalRoute(mostExpensiveArrivalRoute)
    {index=-1;}
    
    City(){};
    
    double getPreference()
    { return preference;}
    double getMaxPossibleTravelTimeSpent()
    { return visitTime+mostExpensiveArrivalRoute;}
    double getMaxPossibleTravelTimeSpentOnStart()
    { return mostExpensiveArrivalRoute*2;}
};

    
    
#endif /* CITY_H_ */
