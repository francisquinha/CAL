//
//  RandomTest.h
//  europa
//
//  Created by Angie on 22/04/2015.
//  Copyright (c) 2015 Angie. All rights reserved.
//

#ifndef __europa__RandomTest__
#define __europa__RandomTest__

#include <vector>
#include "city.h"
#include "Greedy.h"


class TestBNB {
    
    unsigned int numberCities;
    unsigned int maxDist;
    unsigned int minDist;
    unsigned int maxTime;
    unsigned int minTime;
    unsigned int timeLimit;
    std::vector<City> cities;
    
public:
    
    TestBNB(unsigned int numC, unsigned int maxD, unsigned int minD, unsigned int maxT, unsigned int minT);
  
    clock_t runTime();
    
};

class TestGreedy {
    
    unsigned int numberCities;
    unsigned int maxDist;
    unsigned int minDist;
    unsigned int maxTime;
    unsigned int minTime;
    unsigned int timeLimit;
    std::vector<std::vector<double> > adjacency;
    std::vector<double> preference;
    std::vector<unsigned int> tsp;
    std::vector<unsigned int> vrp;
    double tsp_cost {0};
    double vrp_cost {0};
    double vrp_gain {0};
    
public:
    
    TestGreedy(unsigned int numC, unsigned int maxD, unsigned int minD, unsigned int maxT, unsigned int minT);
    
    clock_t runTimeTSP();
    
    clock_t runTimeVRP();

};



#endif /* defined(__europa__RandomTest__) */
