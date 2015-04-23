/*
 * city.h
 *
 *  Created on: 06/04/2015
 *      Author: Bruno
 */

#ifndef CITY_H_
#define CITY_H_

class City{
public:
	std::string name;
	std::string info;
	double preference;
	double visitTime;


	City(std::string name, std::string info, double preference, double visitTime):
		name(name),info(info),preference(preference),visitTime(visitTime)
	{}

	City(){};

	double getPreference()
	{ return preference;}
	double getVisitTime()
		{ return visitTime;}
};

#endif /* CITY_H_ */
