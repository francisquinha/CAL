//
//  RandomTest.cpp
//  europa
//
//  Created by Angie on 22/04/2015.
//  Copyright (c) 2015 Angie. All rights reserved.
//

#include "RandomTest.h"
#include "genericBnB.h"
#include <random>
#include <iostream>

TestBNB::TestBNB(unsigned int numC, unsigned int maxD, unsigned int minD, unsigned int maxT, unsigned int minT) {
    numberCities = numC;
    maxDist = maxD;
    minDist = minD;
    maxTime = maxT;
    minTime = minT;
    timeLimit = rand() % (numC * (maxT + maxD)) + 1;
    cities = {};
    
    for (int i = 0; i < numberCities; i++) {
        unsigned int dist = rand() % (maxDist - minDist + 1) + minDist;
        unsigned int time = rand() % (maxTime - minTime + 1) + minTime;
        unsigned int pref = rand() % 11; //preference int between 0 and 10
        City *city = new City(to_string(i), "0", pref, time, dist);
        cities.push_back(*city);
    }
    
}

clock_t TestBNB::runTime(){
    clock_t ini {clock()};
    BnB_UP<City> bnbCity(cities, timeLimit, &City::getMaxPossibleTravelTimeSpent, &City::getPreference );
    vector<City*> sol = bnbCity.findSolution();
    clock_t fim {clock()};
//    for(int i = 0 ; i<sol.size();i++) cout<<sol[i]->name<<"\n";
    return fim - ini;
}


TestGreedy::TestGreedy(unsigned int numC, unsigned int maxD, unsigned int minD, unsigned int maxT, unsigned int minT) {
    numberCities = numC;
    maxDist = maxD;
    minDist = minD;
    maxTime = maxT;
    minTime = minT;
    timeLimit = rand() % (numC * (maxT + maxD)) + 1;
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

clock_t TestGreedy::runTimeTSP(){
    clock_t ini {clock()};
    GreedyApproxTSP(adjacency, tsp, tsp_cost);
    clock_t fim {clock()};
    return fim - ini;
}

clock_t TestGreedy::runTimeVRP(){
    clock_t ini {clock()};
    GreedyApproxVRP(adjacency, preference, timeLimit, vrp, vrp_gain, vrp_cost);
    clock_t fim {clock()};
    return fim - ini;
}


