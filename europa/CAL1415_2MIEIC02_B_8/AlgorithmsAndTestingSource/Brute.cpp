//
//  Brute.cpp
//  europa
//
//  Created by Angie on 26/04/2015.
//  Copyright (c) 2015 Angie. All rights reserved.
//

#include "Brute.h"
#include "Greedy.h"

using namespace std;

vector<unsigned int> SequenceGenerator(const vector<unsigned int> &inSeq, const unsigned int &i) {
    unsigned int m {i};
    unsigned int n = static_cast<int>(inSeq.size());
    unsigned int d = n;
    vector<unsigned int> outSeq = inSeq;
    while (d > 1) {
        unsigned int r = m % d;
        unsigned int aux = outSeq[n - d + r];
        outSeq[n-d+r] = outSeq[n-d];
        outSeq[n-d] = aux;
        m = (m - r) / d;
        d--;
    }
    return outSeq;
}

unsigned int factorial(unsigned int &n) {
    unsigned int res = 1;
    for (unsigned int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}

void BruteForceTSP(const std::vector<std::vector<double> > &adjacency, std::vector<unsigned int> &tsp, double &tsp_cost) {
    unsigned int number_cities = static_cast<int>(adjacency.size());
    vector<unsigned int> temp {};
    for (unsigned int i = 1; i < number_cities; i++) {
        temp.push_back(i);
    }
    number_cities --;
    unsigned int factor = factorial(number_cities);
    number_cities ++;
    tsp_cost = DBL_INFINITY;
    for (unsigned int i = 0; i < factor; i++) {
        double cost = 0;
        vector<unsigned int> tempo = SequenceGenerator(temp, i);
        tempo.insert(tempo.begin(), 0);
        for (unsigned int j = 1; j < number_cities; j++) {
            unsigned int tempo_j = tempo[j];
            cost += adjacency[tempo[j - 1]][tempo_j] + adjacency [tempo_j][tempo_j];
        }
        cost += adjacency[tempo[number_cities - 1]][0];
        if (cost < tsp_cost) {
            tsp_cost = cost;
            tsp = tempo;
        }
    }
}

void BruteForceVRP(const std::vector<std::vector<double> > &adjacency, const std::vector<double> &preference, const double &limit, std::vector<unsigned int> &vrp, double &vrp_gain, double &vrp_cost) {
    unsigned int number_cities = static_cast<int>(adjacency.size());
    vector<unsigned int> temp {};
    for (unsigned int i = 1; i < number_cities; i++) {
        temp.push_back(i);
    }
    number_cities --;
    unsigned int factor = factorial(number_cities);
    number_cities ++;
    vrp_gain = 0;
    vrp_cost = DBL_INFINITY;
    for (unsigned int i = 0; i < factor; i++) {
        double cost = 0;
        double gain = 0;
        vector<unsigned int> tempo = SequenceGenerator(temp, i);
        tempo.insert(tempo.begin(), 0);
        vector<unsigned int> vrp_temp = {0};
        for (unsigned int j = 1; j < number_cities; j++) {
            unsigned int tempo_j = tempo[j];
            double this_cost = adjacency[tempo[j - 1]][tempo_j] + adjacency [tempo_j][tempo_j];
            double come_back = adjacency[tempo_j][0];
            if (cost + this_cost + come_back <= limit) {
                cost += this_cost;
                gain += preference[tempo_j];
                vrp_temp.push_back(tempo_j);
            }
            else {
                cost += adjacency[tempo[j - 1]][0];
                break;
            }
        }
        if (gain > vrp_gain || (gain == vrp_gain && cost < vrp_cost)) {
            vrp_gain = gain;
            vrp_cost = cost;
            vrp = vrp_temp;
        }
    }
}
