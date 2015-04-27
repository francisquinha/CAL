//
//  Greedy.h
//  europa
//
//  Created by Angie on 24/04/2015.
//  Copyright (c) 2015 Angie. All rights reserved.
//

#ifndef __europa__Greedy__
#define __europa__Greedy__

#include <stdio.h>
#include <vector>
#include <climits>
#include <float.h>

const double DBL_INFINITY = DBL_MAX;

void GreedyApproxTSP(std::vector<std::vector<double> > adjacency, std::vector<unsigned int> &tsp, double &tsp_cost);

void GreedyApproxVRP(std::vector<std::vector<double> > adjacency, std::vector<double> preference, double limit, std::vector<unsigned int> &vrp, double &vrp_gain, double &vrp_cost);

#endif /* defined(__europa__Greedy__) */
