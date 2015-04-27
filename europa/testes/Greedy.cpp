//
//  Greedy.cpp
//  europa
//
//  Created by Angie on 24/04/2015.
//  Copyright (c) 2015 Angie. All rights reserved.
//

#include "Greedy.h"

using namespace std;

void GreedyApproxTSP(const vector<vector<double> > &adjacency, vector<unsigned int> &tsp, double &tsp_cost) {
    unsigned int number_cities = static_cast<int>(adjacency.size());
    unsigned int current_city = 0;
    tsp.push_back(current_city);
    vector<bool> visited;
    visited.push_back(true);
    for (unsigned int i = 1; i < number_cities; i++) visited.push_back(false);
    while (tsp.size() < number_cities) {
        double min_cost = DBL_INFINITY;
        unsigned int min_index = 0;
        for (unsigned int i = 1; i < number_cities; i++) {
            if (visited[i] == false) {
                double cost = adjacency[current_city][i] + adjacency[i][i];
                if (cost < min_cost) {
                    min_cost = cost;
                    min_index = i;
                }
            }
        }
        double cost = adjacency[current_city][min_index] + adjacency[min_index][min_index];
        current_city = min_index;
        visited[current_city] = true;
        tsp.push_back(current_city);
        tsp_cost += cost;
    }
    tsp_cost += adjacency[tsp[number_cities-1]][0];
}

void GreedyApproxVRP(const vector<vector<double> > &adjacency, const vector<double> &preference, const double &limit, vector<unsigned int> &vrp, double &vrp_gain, double &vrp_cost) {
    unsigned int number_cities = static_cast<int>(adjacency.size());
    unsigned int current_city = 0;
    vrp.push_back(current_city);
    vector<bool> visited;
    visited.push_back(true);
    for (unsigned int i = 1; i < number_cities; i++) visited.push_back(false);
    bool fit_more = true;
    while (fit_more) {
        double max_ratio = 0;
        unsigned int max_index = 0;
        for (unsigned int i = 1; i < number_cities; i++) {
            double cost = adjacency[current_city][i] + adjacency[i][i];
            double come_back = adjacency[i][0];
            if (visited[i] == false && limit >= vrp_cost + cost + come_back) {
                double ratio = preference[i] / cost;
                if (ratio > max_ratio) {
                    max_ratio = ratio;
                    max_index = i;
                }
            }
        }
        if (max_ratio != 0) {
            double cost = adjacency[current_city][max_index] + adjacency[max_index][max_index];
            vrp_cost += cost;
            current_city = max_index;
            visited[current_city] = true;
            vrp.push_back(current_city);
            vrp_gain += preference[current_city];
        }
        else fit_more = false;
    }
    vrp_cost += adjacency[vrp[vrp.size()-1]][0];
}


