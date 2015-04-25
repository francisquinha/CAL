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

int main() {

	//tsp like (same values for all
	City cities1[] = {
	City("A","bla bla bla...",3,0),
	City("B","bla bla bla...",3,0),
	City("C","bla bla bla...",3,0),
	City("D","bla bla bla...",3,0),
	City("E","bla bla bla...",3,0)
	};//p/ 65 max = see solution image file
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
	BruteForce<City,double**> bf1(50,citiesV1,0,&edges,&City::getPreference,&City::getVisitTime,getEdgeCostFrom2dArray);
	vector<City*> sol1=bf1.solve(true);
	//vector<City*> sol1=bf1.greedySolve();
	cout<<"\n";
	for(int i = 0 ; i<(int)sol1.size();i++) cout<<sol1[i]->name<<"\n";
	bf1.freeHeap();

	//======2nd test (same as one but excluding C
	City cities2[] = {
	City("A","bla bla bla...",3,0),
	City("B","bla bla bla...",3,0),
	City("C","bla bla bla...",3,50),
	City("D","bla bla bla...",3,0),
	City("E","bla bla bla...",3,0)
	};//p/ 65 max = same order as previous excluding C element
	vector<City> citiesV2 (cities2,&cities2[5]);

	double **edges2;
	edges2=/*new double*[5];*/ (double**) malloc(sizeof(double*)*5);
	edges2[0] = new double[5]{0,5 ,4 ,6 ,5 };//(double*) malloc(sizeof(double)*5);
	edges2[1] = new double[5]{5,0 ,2 ,2 ,6 };
	edges2[2] = new double[5]{4,2 ,0 ,2 ,5 };
	edges2[3] = new double[5]{6,2 ,2 ,0 ,5 };
	edges2[4] = new double[5]{5,6 ,5 ,5 ,0 }; //last line is not really used, just for representation value
	//cout<<edges[1][0];
	//double ***a=&edges; cout<<(*a)[1][0];
	//return 0;
	BruteForce<City,double**> bf2(50,citiesV2,0,&edges2,&City::getPreference,&City::getVisitTime,getEdgeCostFrom2dArray);
	vector<City*> sol2=bf2.solve(true);
	//vector<City*> sol2=bf1.greedySolve();
	cout<<"\n";
	for(int i = 0 ; i<(int)sol2.size();i++) cout<<sol2[i]->name<<"\n";
	bf2.freeHeap();

	//======3rd test (same as 2nd but using different initializer (visit time on the the matrix)
	City cities3[] = {
	City("A","bla bla bla...",3,0),
	City("B","bla bla bla...",3,0),
	City("C","bla bla bla...",3,0),
	City("D","bla bla bla...",3,0),
	City("E","bla bla bla...",3,0)
	};//p/ 65 max = same as previous
	vector<City> citiesV3 (cities3,&cities3[5]);

	double **edges3;
	edges3=/*new double*[5];*/ (double**) malloc(sizeof(double*)*5);
	edges3[0] = new double[5]{0,5 ,4 ,6 ,5 };//(double*) malloc(sizeof(double)*5);
	edges3[1] = new double[5]{5,0 ,2 ,2 ,6 };
	edges3[2] = new double[5]{4,2 ,50 ,2 ,5 };
	edges3[3] = new double[5]{6,2 ,2 ,0 ,5 };
	edges3[4] = new double[5]{5,6 ,5 ,5 ,0 }; //last line is not really used, just for representation value
	//cout<<edges[1][0];
	//double ***a=&edges; cout<<(*a)[1][0];
	//return 0;
	BruteForce<City,double**> bf3(50,citiesV2,0,&edges3,&City::getPreference,getEdgeCostFrom2dArray);
	vector<City*> sol3=bf3.solve(true);
	//vector<City*> sol3=bf1.greedySolve();
	cout<<"\n";
	for(int i = 0 ; i<(int)sol3.size();i++) cout<<sol3[i]->name<<"\n";
	bf3.freeHeap();



	return 0;
}
