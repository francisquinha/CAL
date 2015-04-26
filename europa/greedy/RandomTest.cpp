//
//  RandomTest.cpp
//  europa
//
//  Created by Angie on 22/04/2015.
//  Copyright (c) 2015 Angie. All rights reserved.
//

#include "RandomTest.h"

using namespace std;

void convertData(vector<City> &v, int numElems, vector<vector<double> > &elems, vector<double> &prefs) {
    //note:consider 1st city to be the start checkpoint

    //create max edges with 0's
    double maxEdges[numElems];
    for(int i = 0;i<numElems;i++)maxEdges[i]=0;

    //get cities and max edges
    for(int i = 0;i<numElems;i++)
        for(int j = i;j<numElems;j++) {
            stringstream ss {};
            if (elems[i][j]>maxEdges[i]) maxEdges[i] = elems[i][j];
            if (elems[i][j]>maxEdges[j]) maxEdges[j] = elems[i][j];
            ss << i;
            if (i==j) v.push_back(City(ss.str(),"",prefs[i] ,i ,0 ));
        }

    //assign max edges and preferences to each city
    for(int i = 0; i<numElems;i++) {v[i].mostExpensiveArrivalRoute = maxEdges[i]; v[i].preference = prefs[i];}
}


double getEdgeCost(City *c1, City *c2, int i1, int i2, vector<vector<double> > *edges) {
    //could be more complicated, like searching a list for each vertex pair
    return (*edges)[i1][i2];
}

TestTime::TestTime(unsigned int numC, unsigned int maxD, unsigned int minD, unsigned int maxT, unsigned int minT) {
    numberCities = numC;
    maxDist = maxD;
    minDist = minD;
    maxTime = maxT;
    minTime = minT;
    timeLimit = numC * (maxT + maxD);
//    timeLimit = rand() % (numC * (maxT + maxD)) + 1;
    adjacency = {};
    preference = {};
    
    for (unsigned int i = 0; i < numberCities; i++) {
        vector<double> adjacency_line {};
        for (unsigned int j = 0; j < numberCities; j++) {
            adjacency_line.push_back(rand() % (maxDist - minDist + 1) + minDist);
        }
        adjacency.push_back(adjacency_line);
        adjacency[i][i] = rand() % (maxTime - minTime + 1) + minTime;
        preference.push_back(rand() % 11); //preference between 0 and 10
    }
}

clock_t TestTime::runTimeTSP(){
    clock_t ini {clock()};
    GreedyApproxTSP(adjacency, tsp, tsp_cost);
    clock_t fim {clock()};
    return fim - ini;
}

clock_t TestTime::runTimeVRP(){
    clock_t ini {clock()};
    GreedyApproxVRP(adjacency, preference, timeLimit, vrp, vrp_gain, vrp_cost);
    clock_t fim {clock()};
    return fim - ini;
}

clock_t TestTime::runTimeBF() {
    vector<City> cities {};
    convertData(cities, numberCities, adjacency, preference);
    BruteForce<City, vector<vector<double> > > BF (timeLimit, cities, 0, &adjacency, &City::getPreference, getEdgeCost);
    clock_t ini {clock()};
    vector<City*> sol = BF.solve(false); // optime = false para retornar assim que achar uma solucao maxima (nao necessariamente a mais rapida das maximas)
    clock_t fim {clock()};
    BF.freeHeap();
    return fim - ini;
}

clock_t TestTime::runTimeBFG() {
    vector<City> cities {};
    convertData(cities, numberCities, adjacency, preference);
    BruteForce<City, vector<vector<double> > > BF (timeLimit, cities, 0, &adjacency, &City::getPreference, getEdgeCost);
    clock_t ini {clock()};
    vector<City*> sol=BF.greedySolve();
    clock_t fim {clock()};
    BF.freeHeap();
    return fim - ini;
}

clock_t TestTime::runTimeBnB(){
    vector<City> cities {};
    convertData(cities, numberCities, adjacency, preference);
    BnB_UP<City> BnB(cities, &City::getMaxPossibleTravelTimeSpent, &City::getPreference);
    clock_t ini {clock()};
    vector<City*> sol = BnB.problem8ApproximateSolve(&cities[0], &City::getMaxPossibleTravelTimeSpentOnStart, timeLimit);
    clock_t fim {clock()};
    BnB.freeHeap();
    return fim - ini;
}

