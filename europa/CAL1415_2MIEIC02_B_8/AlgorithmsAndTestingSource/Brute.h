//
//  Brute.h
//  europa
//
//  Created by Angie on 26/04/2015.
//  Copyright (c) 2015 Angie. All rights reserved.
//

#ifndef __europa__Brute__
#define __europa__Brute__

#include <stdio.h>
#include <vector>
#include <climits>
#include <float.h>

std::vector<unsigned int> SequenceGenerator(const std::vector<unsigned int> &inSeq, const unsigned int &i);

unsigned int factorial(unsigned int &n);

void BruteForceTSP(const std::vector<std::vector<double> > &adjacency, std::vector<unsigned int> &tsp, double &tsp_cost);

void BruteForceVRP(const std::vector<std::vector<double> > &adjacency, const std::vector<double> &preference, const double &limit, std::vector<unsigned int> &vrp, double &vrp_gain, double &vrp_cost);

#endif /* defined(__europa__Brute__) */
