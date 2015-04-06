/*
 * city.h
 *
 *  Created on: 06/04/2015
 *      Author: Bruno
 */

#ifndef CITY_H_
#define CITY_H_

class City{

	std::string name;
	std::string info;
	double preference;
	double visitTime;
	double mostExpensiveArrivalRoute;

public:
	City(std::string name, std::string info, double preference, double visitTime, double mostExpensiveArrivalRoute):
		name(name),info(info),preference(preference),visitTime(visitTime),mostExpensiveArrivalRoute(mostExpensiveArrivalRoute)
	{}

	double getPreference()
	{ return preference;}
	double getMaxPossibleTravelTimeSpent()
	{ return visitTime+mostExpensiveArrivalRoute;}
};



#endif /* CITY_H_ */
