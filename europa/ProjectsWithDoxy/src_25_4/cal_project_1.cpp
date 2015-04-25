//============================================================================
// Name        : cal_project_1.cpp
// Author      : Bruno Madeira
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
/* rand example: guess the number */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "city.h"
#include <vector>
#include <limits>
using namespace std;

#define NUMBER_OF_TEST 1

/*void generateTestData(int &numElems,double**&pesos,double*&preferences,int min, int max)
{
	numElems= rand()%100;

	preferences=(double*) malloc(sizeof(double)*numElems);
	for(int i = 0;i<numElems;i++) preferences[i]=rand()%10;

	pesos= (double**) malloc(sizeof(double*)*numElems);
	for(int i = 0;i<numElems;i++) pesos[i] = (double*) malloc(sizeof(double)*numElems);

	int dif=max-min;
	for(int i = 0;i<numElems-1;i++)
		for(int j = i;j<numElems;j++)
		{
			pesos[i][j]=rand()%(dif)+min;
			pesos[j][i]=pesos[i][j];
		}
}

void freeTestData(int numElems,double**&elems,double*&preferences)
{
	for(int i = 0;i<numElems;i++) free(elems[i]);
	free(elems);
	free(preferences);
}*/

void convertDataToAproximateSolutionWithBNBinput(vector<City*> &v,int numElems,double**&elems,double*&prefs)
{
	//note:consider 1st city to be the start checkpoint

	//create max edges with 0's
	double maxEdges[numElems];
	for(int i = 0;i<numElems;i++)maxEdges[i]=0;

	//get cities and max edges
	for(int i = 0;i<numElems-1;i++)
		for(int j = i;j<numElems;j++)
		{
			char cityIndex[20];
			if (elems[i][j]>maxEdges[i]) maxEdges[i] = elems[i][j];
			if (elems[i][j]>maxEdges[j]) maxEdges[j] = elems[i][j];
			itoa (i,cityIndex,10);
			if (i==j) v.push_back(new City(cityIndex,"",prefs[i] ,i ,0 ));
		}

	//assign max edges and preferences to each city
	for(int i = 0; i<numElems;i++) {v[i]->mostExpensiveArrivalRoute = maxEdges[i]; v[i]->preference = prefs[i];}
}


double getEdgeCostFrom2dArray(City *c1, City *c2,int i1,int i2,double ***edges)
{
	//could be more complicated, like searching a list for each vertex pair
	return (*edges)[i1][i2];
}


int main() {
	return 0;
}
