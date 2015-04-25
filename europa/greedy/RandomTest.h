//
//  RandomTest.h
//  europa
//
//  Created by Angie on 22/04/2015.
//  Copyright (c) 2015 Angie. All rights reserved.
//

#ifndef __europa__RandomTest__
#define __europa__RandomTest__

#include <random>
#include <iostream>
#include <vector>
#include <sstream>
#include "city.h"
#include "Greedy.h"
#include "genericBnB.h"
#include "bruteForce.h"

class TestTime {
    
    unsigned int numberCities;
    unsigned int maxDist;
    unsigned int minDist;
    unsigned int maxTime;
    unsigned int minTime;
    unsigned int timeLimit;
    vector<vector<double> > adjacency;
    vector<double> preference;
    vector<unsigned int> tsp;
    vector<unsigned int> vrp;
    double tsp_cost {0};
    double vrp_cost {0};
    double vrp_gain {0};

public:
    
    TestTime(unsigned int numC, unsigned int maxD, unsigned int minD, unsigned int maxT, unsigned int minT);
    
    clock_t runTimeTSP();
    
    clock_t runTimeVRP();
    
    clock_t runTimeBF();

    clock_t runTimeBFG();

    clock_t runTimeBnB();
    
//    void convertData(vector<City*> &cities,int numCit, vector<vector<double> > &adjac, vector<double> &pref);
    
//    double getEdgeCostFrom2dArray(City *c1, City *c2,int i1,int i2,double ***edges);

};



#endif /* defined(__europa__RandomTest__) */
