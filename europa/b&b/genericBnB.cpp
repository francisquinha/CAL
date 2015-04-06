//============================================================================
// Name        : genericBnB.cpp
// Author      : Bruno Madeira
// Version     :
// Copyright   : developed in academic context. use freely =)
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "city.h"
#include "genericBnB.h"
//using namespace std;

int main() {

	City cities[] = {
	City("London","Capital of England. bla bla bla...",20,7,3),//2
	City("Madrid","Capital of Spain. bla bla bla...",60,18,2),//3
	City("Paris","Capital of France. bla bla bla...",10,5,5)//1
	};
	vector<City> citiesV (cities,&cities[3]);

	BnB_UP<City> bnbCity(citiesV, 50,&City::getMaxPossibleTravelTimeSpent,&City::getPreference );

	cout << "END" << endl; // prints !!!Hello World!!!
	return 0;
}
