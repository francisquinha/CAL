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
#include "Brute.h"
#include "genericBnB.h"
#include "bruteForce.h"
#include <ctime>

class TestTime {
    
    unsigned int numberCities;
    unsigned int maxDist;
    unsigned int minDist;
    unsigned int maxTime;
    unsigned int minTime;
    unsigned long timeLimit;
    unsigned long notimeLimit;
    vector<vector<double> > adjacency;
    vector<double> preference;
    vector<unsigned int> tsp;
    vector<unsigned int> vrp;
    double tsp_cost {0};
    double vrp_cost {0};
    double vrp_gain {0};
    vector<unsigned int> bf_tsp;
    vector<unsigned int> bf_vrp;
    double bf_tsp_cost {0};
    double bf_vrp_cost {0};
    double bf_vrp_gain {0};

public:
    
    TestTime(unsigned int numC, unsigned int maxD, unsigned int minD, unsigned int maxT, unsigned int minT);
    
    clock_t runTimeTSP();
    
    clock_t runTimeVRP();
    
    clock_t runTimeBFTSP();
    
    clock_t runTimeBFVRP();
    
    clock_t runTimeTSPBF();

    clock_t runTimeVRPBF();

    clock_t runTimeBFG();

    clock_t runTimeBnB();
    
    void BFTSPsol(vector<vector<double> > &adjac, vector<double> &pref, vector<City*> &bftsp);
    
    void BFVRPsol(vector<vector<double> > &adjac, vector<double> &pref, unsigned int &limit, vector<City*> &bfvrp);

    vector<double> qualityTSP();
    
    vector<double> qualityVRP();

};



#endif /* defined(__europa__RandomTest__) */
