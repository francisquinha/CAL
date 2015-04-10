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
	BnB_UP<City> bnbCity(citiesV, 11,&City::getMaxPossibleTravelTimeSpent,&City::getPreference );
	vector<City*> sol1 = bnbCity.findSolution();


	City* m=new Manchester();
	((Manchester*) &m)->a=3;
	cout<<"debugA:"<<((Manchester*) &m)->a;


	cout<<"debug1:\n";
	cout<<bnbCity.minItemCost<<"\n";
	for(int i = 0 ; i<sol1.size();i++) cout<<sol1[i]->name<<"\n";
	cout<<"debug1 ended \n";

	/*
	BnB_node b1={1,1,10,1};
	BnB_node b2={1,1,20,1};
	BnB_node b3={1,1,5,1};
	BnB_node b4={1,1,10,1};
	BnB_node b5={1,1,3,1};
	BnB_node b6={1,1,14,1};
	priority_queue<BnB_node> nodesQ;
	nodesQ.push(b1);
	nodesQ.push(b2);
	nodesQ.push(b3);
	nodesQ.push(b4);
	nodesQ.push(b5);
	nodesQ.push(b6);
	while(nodesQ.size()>0) { cout<<nodesQ.top().bound<<"\n"; nodesQ.pop();  }
	*/
	/*
	City cities3[] = {
	City("A","bla bla bla...",2,3,5),
	City("B","bla bla bla...",6,2,6),
	City("C","bla bla bla...",3,1,2),
	City("D","bla bla bla...",9,1,8),
	City("E","bla bla bla...",1,2,7),
	City("F","bla bla bla...",2,4,5),
	City("G","bla bla bla...",5,3,9),
	City("H","bla bla bla...",8,5,7),
	City("I","bla bla bla...",7,4,3),
	City("J","bla bla bla...",4,5,4),
	City("L","bla bla bla...",2,1,7),
	City("K","bla bla bla...",4,2,2)
	};
	vector<City> citiesV3 (cities3,&cities3[12]);
	BnB_UP<City> bnbCity(citiesV3, 31,&City::getMaxPossibleTravelTimeSpent,&City::getPreference );

	*/

	cout << "END" << endl; // prints !!!Hello World!!!
	return 0;
}
