//============================================================================
// Name        : bruteForce.cpp
// Author      : Bruno Madeira
// Version     :
// Copyright   : developed in academic context. use freely =)
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "bruteForce.h"
#include "city.h"

using namespace std;

double getEdgeCostFrom2dArray(City *c1, City *c2,int i1,int i2,double ***edges)
{
	//could be more complicated, like searching a list for each vertex pair
	return (*edges)[i1][i2];
}

//typedef void* pointerToStuff;

int main() {

	//tsp like (same values for all
	City cities1[] = {
	City("A","bla bla bla...",3,0),
	City("B","bla bla bla...",3,0),
	City("C","bla bla bla...",3,0),
	City("D","bla bla bla...",3,0),
	City("E","bla bla bla...",3,0)
	};//p/ 65 max = E,F,H,J
	vector<City> citiesV1 (cities1,&cities1[5]);

	double **edges;
	edges=/*new double*[5];*/ (double**) malloc(sizeof(double*)*5);
	edges[0] = new double[5]{0,5 ,4 ,6 ,5 };//(double*) malloc(sizeof(double)*5);
	edges[1] = new double[5]{5,0 ,2 ,2 ,6 };
	edges[2] = new double[5]{4,2 ,0 ,2 ,5 };
	edges[3] = new double[5]{6,2 ,2 ,0 ,5 };
	edges[4] = new double[5]{5,6 ,5 ,5 ,0 }; //last line is not really used, just for representation value
	//cout<<edges[1][0];
	//double ***a=&edges; cout<<(*a)[1][0];
	//return 0;
	//solucao=acbde ou o reverse edbca
	BruteForce<City,double**> bf1(true,50,citiesV1,0,&edges,&City::getPreference,&City::getVisitTime,getEdgeCostFrom2dArray);
	vector<City*> sol1=bf1.solve();
	cout<<"\n";
	for(int i = 0 ; i<(int)sol1.size();i++) cout<<sol1[i]->name<<"\n";


	return 0;
}
