//
//  main.cpp
//  europa
//
//  Created by Angie on 22/04/2015.
//  Copyright (c) 2015 Angie. All rights reserved.
//

#include <iostream>
#include "RandomTest.h"

using namespace std;

int main() {
/*
    vector<unsigned int> seq = {1, 2, 3, 4};
    for (unsigned int i = 0; i < 24; i++) {
        vector<unsigned int> seqo = SequenceGenerator(seq, i);
        for (unsigned int j = 0; j < 4; j++) {
            cout << seqo[j] << " ";
        }
        cout << endl;
    }
*/
/*
    TestTime *test = new TestTime(10, 20, 1, 10, 1);

    vector<vector<double> > adjacency1 = {
        {0, 2, 3, 1},
        {2, 2, 5, 2},
        {3, 5, 3, 3},
        {1, 2, 3, 2}
    };
    vector<double> preference1 = {0, 7, 8, 5};
    unsigned int limit1 = 15;
    vector<unsigned int> tsp1 = {};
    double tsp_cost1 {0};
    vector<unsigned int> vrp1 = {};
    double vrp_gain1 {0};
    double vrp_cost1 {0};
    GreedyApproxTSP(adjacency1, tsp1, tsp_cost1);
    cout << "GTSP ";
    for (unsigned int i = 0; i < tsp1.size(); i++) {
        cout << tsp1[i] << " -> ";
    }
    cout << tsp1[0] << endl;
    cout << tsp_cost1 << endl;
    vector<unsigned int> bftsp1 = {};
    double bftsp_cost1 {0};
    vector<unsigned int> bfvrp1 = {};
    double bfvrp_gain1 {0};
    double bfvrp_cost1 {0};
    BruteForceTSP(adjacency1, bftsp1, bftsp_cost1);
    cout << "BTSP ";
    for (unsigned int i = 0; i < tsp1.size(); i++) {
        cout << bftsp1[i] << " -> ";
    }
    cout << bftsp1[0] << endl;
    cout << bftsp_cost1 << endl;
    GreedyApproxVRP(adjacency1, preference1, limit1, vrp1, vrp_gain1, vrp_cost1);
    cout << "GVRP ";
    for (unsigned int i = 0; i < vrp1.size(); i++) {
        cout << vrp1[i] << " -> ";
    }
    cout << vrp1[0] << endl;
    cout << vrp_gain1 << " " << vrp_cost1 << endl;
    BruteForceVRP(adjacency1, preference1, limit1, bfvrp1, bfvrp_gain1, bfvrp_cost1);
    cout << "BVRP ";
    for (unsigned int i = 0; i < bfvrp1.size(); i++) {
        cout << bfvrp1[i] << " -> ";
    }
    cout << bfvrp1[0] << endl;
    cout << bfvrp_gain1 << " " << bfvrp_cost1 << endl;
    
    vector<City*> bbftsp1 {};
    test->BFTSPsol(adjacency1, preference1, bbftsp1);
    cout << "TSPB ";
    cout << "0 -> ";
    for (unsigned int i = 0; i < bbftsp1.size(); i++) {
        cout << bbftsp1[i]->name << " -> ";
    }
    cout << "0" << endl;
    vector<City*> bbfvrp1 {};
    cout << "VRPB ";
    cout << "0 -> ";
    test->BFVRPsol(adjacency1, preference1, limit1, bbfvrp1);
    for (unsigned int i = 0; i < bbfvrp1.size(); i++) {
        cout << bbfvrp1[i]->name << " -> ";
    }
    cout << "0" << endl;
    
    cout << endl << endl;

    vector<vector<double> > adjacency2 = {
        {0, 2, 4, 1, 3},
        {2,	4, 5, 3, 2},
        {4,	5, 4, 3, 6},
        {1,	3, 3, 3, 7},
        {3,	2, 6, 7, 6}
    };
    vector<double> preference2 = {0, 2, 7, 5, 3};
    unsigned int limit2 = 25;
    vector<unsigned int> tsp2 = {};
    double tsp_cost2 {0};
    vector<unsigned int> vrp2 = {};
    double vrp_gain2 {0};
    double vrp_cost2 {0};
    GreedyApproxTSP(adjacency2, tsp2, tsp_cost2);
    cout << "GTSP ";
    for (unsigned int i = 0; i < tsp2.size(); i++) {
        cout << tsp2[i] << " -> ";
    }
    cout << tsp2[0] << endl;
    cout << tsp_cost2 << endl;
    vector<unsigned int> bftsp2 = {};
    double bftsp_cost2 {0};
    vector<unsigned int> bfvrp2 = {};
    double bfvrp_gain2 {0};
    double bfvrp_cost2 {0};
    BruteForceTSP(adjacency2, bftsp2, bftsp_cost2);
    cout << "BTSP ";
    for (unsigned int i = 0; i < tsp2.size(); i++) {
        cout << bftsp2[i] << " -> ";
    }
    cout << bftsp2[0] << endl;
    cout << bftsp_cost2 << endl;
    GreedyApproxVRP(adjacency2, preference2, limit2, vrp2, vrp_gain2, vrp_cost2);
    cout << "GVRP ";
    for (unsigned int i = 0; i < vrp2.size(); i++) {
        cout << vrp2[i] << " -> ";
    }
    cout << vrp2[0] << endl;
    cout << vrp_gain2 << " " << vrp_cost2 << endl;
    BruteForceVRP(adjacency2, preference2, limit2, bfvrp2, bfvrp_gain2, bfvrp_cost2);
    cout << "BVRP ";
    for (unsigned int i = 0; i < bfvrp2.size(); i++) {
        cout << bfvrp2[i] << " -> ";
    }
    cout << bfvrp2[0] << endl;
    cout << bfvrp_gain2 << " " << bfvrp_cost2 << endl;
    
    vector<City*> bbftsp2 {};
    test->BFTSPsol(adjacency2, preference2, bbftsp2);
    cout << "TSPB ";
    cout << "0 -> ";
    for (unsigned int i = 0; i < bbftsp2.size(); i++) {
        cout << bbftsp2[i]->name << " -> ";
    }
    cout << "0" << endl;
    vector<City*> bbfvrp2 {};
    test->BFVRPsol(adjacency2, preference2, limit2, bbfvrp2);
    cout << "VRPB ";
    cout << "0 -> ";
    for (unsigned int i = 0; i < bbfvrp2.size(); i++) {
        cout << bbfvrp2[i]->name << " -> ";
    }
    cout << "0" << endl;
*/
/*
    srand (static_cast<int>(time(NULL)));
    
    unsigned int number_tests = 1000;
    
    unsigned int number_cities = 1000;
    
    double avg_clock_tsp {0};
    double avg_clock_vrp {0};
    double avg_clock_bnb {0};
//    double avg_clock_bftsp {0};
//    double avg_clock_bfvrp {0};
//    double avg_clock_bfg {0};
    for (unsigned int i = 0; i < number_tests; i++) {
        TestTime *test = new TestTime(number_cities, 20, 1, 3, 1);
        avg_clock_tsp += test->runTimeTSP();
        avg_clock_vrp += test->runTimeVRP();
        avg_clock_bnb += test->runTimeBnB();
//        avg_clock_bftsp += test->runTimeBFTSP();
//        avg_clock_bfvrp += test->runTimeBFVRP();
//        avg_clock_bftsp += test->runTimeTSPBF();
//        avg_clock_bfvrp += test->runTimeVRPBF();
//        avg_clock_bfg += test->runTimeBFG();
        delete test;
    }
    avg_clock_tsp /= number_tests;
    avg_clock_vrp /= number_tests;
    avg_clock_bnb /= number_tests;
//    avg_clock_bftsp /= number_tests;
//    avg_clock_bfvrp /= number_tests;
//    avg_clock_bfg /= number_tests;
    cout << static_cast<int>(avg_clock_tsp) << endl;
    cout << static_cast<int>(avg_clock_vrp) << endl;
    cout << static_cast<int>(avg_clock_bnb) << endl;
//    cout << static_cast<int>(avg_clock_bftsp) << endl;
//    cout << static_cast<int>(avg_clock_bfvrp) << endl;
//    cout << static_cast<int>(avg_clock_bfg) << endl;
*/
    
    srand (static_cast<int>(time(NULL)));
    
    unsigned int number_tests = 1000;
    
    unsigned int number_cities = 10;
    
    double avg_cost_tsp {0};
    double avg_cost_tspbf {0};
    double avg_gain_vrp {0};
    double avg_gain_bnb {0};
    double avg_gain_vrpbf {0};
    unsigned int ups = 0;
    for (unsigned int i = 0; i < number_tests; i++) {
        TestTime *test = new TestTime(number_cities, 10, 7, 3, 1);
        vector<double> qualTSP = test->qualityTSP();
        avg_cost_tsp += qualTSP[0];
        avg_cost_tspbf += qualTSP[1];
        vector<double> qualVRP = test->qualityVRP();
        avg_gain_vrp += qualVRP[0];
        avg_gain_bnb += qualVRP[1];
        avg_gain_vrpbf +=qualVRP[2];
        if (qualVRP[0] > qualVRP[2]) ups++;
        delete test;
    }
    avg_cost_tsp /= number_cities;
    avg_cost_tspbf /= number_cities;
    avg_gain_vrp /= number_cities;
    avg_gain_bnb /= number_cities;
    avg_gain_vrpbf /= number_cities;
    
    cout << static_cast<int>(avg_cost_tsp) << endl;
    cout << static_cast<int>(avg_cost_tspbf) << endl;
    cout << static_cast<int>(avg_gain_vrp) << endl;
    cout << static_cast<int>(avg_gain_bnb) << endl;
    cout << static_cast<int>(avg_gain_vrpbf) << endl;
    cout << ups << endl;
    
}
