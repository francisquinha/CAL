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
            if (i==j) v.push_back(City(ss.str(), "", prefs[i], elems[i][i], 0));
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
    timeLimit = rand() % (numC * (maxT + maxD)) + 1;
    notimeLimit = numC * (maxT + maxD);
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
    adjacency[0][0] = 0; // nao se visita a cidade de partida
    preference[0] = 0; // nao ha preferencia para a cidade de partida
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

clock_t TestTime::runTimeBFTSP(){
    clock_t ini {clock()};
    BruteForceTSP(adjacency, bf_tsp, bf_tsp_cost);
    clock_t fim {clock()};
    return fim - ini;
}

clock_t TestTime::runTimeBFVRP(){
    clock_t ini {clock()};
    BruteForceVRP(adjacency, preference, timeLimit, bf_vrp, bf_vrp_gain, bf_vrp_cost);
    clock_t fim {clock()};
    return fim - ini;
}

clock_t TestTime::runTimeTSPBF() {
    vector<City> cities {};
    clock_t ini {clock()};
    convertData(cities, numberCities, adjacency, preference);
    BruteForce<City, vector<vector<double> > > BF (notimeLimit, cities, 0, &adjacency, &City::getPreference, getEdgeCost);
    vector<City*> sol = BF.solve(true); // optime = false para retornar assim que achar uma solucao maxima (nao necessariamente a mais rapida das maximas)
    clock_t fim {clock()};
    BF.freeHeap();
    return fim - ini;
}

clock_t TestTime::runTimeVRPBF() {
    vector<City> cities {};
    clock_t ini {clock()};
    convertData(cities, numberCities, adjacency, preference);
    BruteForce<City, vector<vector<double> > > BF (timeLimit, cities, 0, &adjacency, &City::getPreference, getEdgeCost);
    vector<City*> sol = BF.solve(true); // optime = false para retornar assim que achar uma solucao maxima (nao necessariamente a mais rapida das maximas)
    clock_t fim {clock()};
    BF.freeHeap();
    return fim - ini;
}

clock_t TestTime::runTimeBFG() {
    vector<City> cities {};
    clock_t ini {clock()};
    convertData(cities, numberCities, adjacency, preference);
    BruteForce<City, vector<vector<double> > > BF (timeLimit, cities, 0, &adjacency, &City::getPreference, getEdgeCost);
    vector<City*> sol=BF.greedySolve();
    clock_t fim {clock()};
    BF.freeHeap();
    return fim - ini;
}

clock_t TestTime::runTimeBnB(){
    vector<City> cities {};
    clock_t ini {clock()};
    convertData(cities, numberCities, adjacency, preference);
    BnB_UP<City> BnB(cities, &City::getMaxPossibleTravelTimeSpent, &City::getPreference);
    vector<City*> sol = BnB.problem8ApproximateSolve(&cities[0], &City::getMaxPossibleTravelTimeSpentOnStart, timeLimit);
    clock_t fim {clock()};
    BnB.freeHeap();
    return fim - ini;
}

void TestTime::BFTSPsol(vector<vector<double> > &adjac, vector<double> &pref, vector<City*> &bftsp) {
    vector<City> cities {};
    convertData(cities, static_cast<int>(adjac.size()), adjac, pref);
    unsigned int nolimit{0};
    for (unsigned int i = 0; i < adjac.size(); i++) {
        for (unsigned int j = 0; j < adjac.size(); j++) {
            nolimit += adjac[i][j];
        }
    }
    BruteForce<City, vector<vector<double> > > BF (nolimit, cities, 0, &adjac, &City::getPreference, getEdgeCost);
    bftsp = BF.solve(true); // optime = false para retornar assim que achar uma solucao maxima (nao necessariamente a mais rapida das maximas)
    BF.freeHeap();
}

void TestTime::BFVRPsol(vector<vector<double> > &adjac, vector<double> &pref, unsigned int &limit, vector<City*> &bfvrp) {
    vector<City> cities {};
    convertData(cities, static_cast<int>(adjac.size()), adjac, pref);
    BruteForce<City, vector<vector<double> > > BF (limit, cities, 0, &adjac, &City::getPreference, getEdgeCost);
    bfvrp = BF.solve(true); // optime = false para retornar assim que achar uma solucao maxima (nao necessariamente a mais rapida das maximas)
    BF.freeHeap();
}

vector<double> TestTime::qualityTSP() {
    GreedyApproxTSP(adjacency, tsp, tsp_cost);
    BruteForceTSP(adjacency, bf_tsp, bf_tsp_cost);
    vector<double> res = {tsp_cost, bf_tsp_cost};
    return res;
}

vector<double> TestTime::qualityVRP() {
    GreedyApproxVRP(adjacency, preference, timeLimit, vrp, vrp_gain, vrp_cost);
    BruteForceVRP(adjacency, preference, timeLimit, bf_vrp, bf_vrp_gain, bf_vrp_cost);
    vector<City> cities {};
    convertData(cities, numberCities, adjacency, preference);
    BnB_UP<City> BnB(cities, &City::getMaxPossibleTravelTimeSpent, &City::getPreference);
    vector<City*> sol = BnB.problem8ApproximateSolve(&cities[0], &City::getMaxPossibleTravelTimeSpentOnStart, timeLimit);
    double gain {0};
    for (unsigned int i = 0; i < sol.size(); i++) {
        gain += sol[i]->preference;
    }
    BnB.freeHeap();
    vector<double> res = {vrp_gain, gain, bf_vrp_gain};
    return res;
}
