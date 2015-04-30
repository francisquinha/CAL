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

void testSequanceGenerator(unsigned int n) {
    vector<unsigned int> seq = {};
    for (unsigned int i = 1; i < n; i++) {
        seq.push_back(i);
    }
    n--;
    unsigned int factor = factorial(n);
    n++;
    for (unsigned int i = 0; i < factor; i++) {
        vector<unsigned int> seqo = SequenceGenerator(seq, i);
        for (unsigned int j = 0; j < 4; j++) {
            cout << seqo[j] << " ";
        }
        cout << endl;
    }
}

void testResult() {
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
    cout << "cost " << tsp_cost1 << endl;
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
    cout << "cost " << bftsp_cost1 << endl;
    GreedyApproxVRP(adjacency1, preference1, limit1, vrp1, vrp_gain1, vrp_cost1);
    cout << "GVRP ";
    for (unsigned int i = 0; i < vrp1.size(); i++) {
        cout << vrp1[i] << " -> ";
    }
    cout << vrp1[0] << endl;
    cout << "gain " << vrp_gain1 << " cost " << vrp_cost1 << endl;
    BruteForceVRP(adjacency1, preference1, limit1, bfvrp1, bfvrp_gain1, bfvrp_cost1);
    cout << "BVRP ";
    for (unsigned int i = 0; i < bfvrp1.size(); i++) {
        cout << bfvrp1[i] << " -> ";
    }
    cout << bfvrp1[0] << endl;
    cout << "gain " << bfvrp_gain1 << " cost " << bfvrp_cost1 << endl;
    
    vector<City*> bbftsp1 {};
    test->BFTSPsol(adjacency1, preference1, bbftsp1);
    cout << "OTSP ";
    cout << "0 -> ";
    double bbftsp_cost1{0};
    for (unsigned int i = 0; i < bbftsp1.size(); i++) {
        cout << bbftsp1[i]->name << " -> ";
        if (i == 0) bbftsp_cost1 += adjacency1[0][atoi((bbftsp1[i]->name).c_str())];
        else bbftsp_cost1 += adjacency1[atoi((bbftsp1[i-1]->name).c_str())][atoi((bbftsp1[i]->name).c_str())];
        bbftsp_cost1 += bbftsp1[i]->visitTime;
    }
    bbftsp_cost1 += adjacency1[atoi((bbftsp1[bbftsp1.size() - 1 ]->name).c_str())][0];
    cout << "0" << endl;
    cout << "cost " << bbftsp_cost1 << endl;
    vector<City*> bbfvrp1 {};
    cout << "OVRP ";
    cout << "0 -> ";
    test->BFVRPsol(adjacency1, preference1, limit1, bbfvrp1);
    double bbfvrp_gain1{0};
    double bbfvrp_cost1{0};
    for (unsigned int i = 0; i < bbfvrp1.size(); i++) {
        cout << bbfvrp1[i]->name << " -> ";
        bbfvrp_gain1 += bbfvrp1[i]->preference;
        if (i == 0) bbfvrp_cost1 += adjacency1[0][atoi((bbfvrp1[i]->name).c_str())];
        else bbfvrp_cost1 += adjacency1[atoi((bbfvrp1[i-1]->name).c_str())][atoi((bbfvrp1[i]->name).c_str())];
        bbfvrp_cost1 += bbfvrp1[i]->visitTime;
    }
    bbfvrp_cost1 += adjacency1[atoi((bbfvrp1[bbfvrp1.size() - 1 ]->name).c_str())][0];
    cout << "0" << endl;
    cout << "gain " << bbfvrp_gain1 << " cost " << bbfvrp_cost1 << endl;

    cout << endl;
    
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
    cout << "cost " << tsp_cost2 << endl;
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
    cout << "cost " << bftsp_cost2 << endl;
    GreedyApproxVRP(adjacency2, preference2, limit2, vrp2, vrp_gain2, vrp_cost2);
    cout << "GVRP ";
    for (unsigned int i = 0; i < vrp2.size(); i++) {
        cout << vrp2[i] << " -> ";
    }
    cout << vrp2[0] << endl;
    cout << "gain " << vrp_gain2 << " cost " << vrp_cost2 << endl;
    BruteForceVRP(adjacency2, preference2, limit2, bfvrp2, bfvrp_gain2, bfvrp_cost2);
    cout << "BVRP ";
    for (unsigned int i = 0; i < bfvrp2.size(); i++) {
        cout << bfvrp2[i] << " -> ";
    }
    cout << bfvrp2[0] << endl;
    cout << "gain " << bfvrp_gain2 << " cost " << bfvrp_cost2 << endl;
    
    vector<City*> bbftsp2 {};
    test->BFTSPsol(adjacency2, preference2, bbftsp2);
    cout << "OTSP ";
    cout << "0 -> ";
    double bbftsp_cost2{0};
    for (unsigned int i = 0; i < bbftsp2.size(); i++) {
        cout << bbftsp2[i]->name << " -> ";
        if (i == 0) bbftsp_cost2 += adjacency2[0][atoi((bbftsp2[i]->name).c_str())];
        else bbftsp_cost2 += adjacency2[atoi((bbftsp2[i - 1]->name).c_str())][atoi((bbftsp2[i]->name).c_str())];
        bbftsp_cost2 += bbftsp2[i]->visitTime;
    }
    bbftsp_cost2 += adjacency2[atoi((bbftsp2[bbftsp2.size() - 1]->name).c_str())][0];
    cout << "0" << endl;
    cout << "cost " << bbftsp_cost2 << endl;
    vector<City*> bbfvrp2 {};
    cout << "OVRP ";
    cout << "0 -> ";
    test->BFVRPsol(adjacency2, preference2, limit2, bbfvrp2);
    double bbfvrp_gain2{0};
    double bbfvrp_cost2{0};
    for (unsigned int i = 0; i < bbfvrp2.size(); i++) {
        cout << bbfvrp2[i]->name << " -> ";
        bbfvrp_gain2 += bbfvrp2[i]->preference;
        if (i == 0) bbfvrp_cost2 += adjacency2[0][atoi((bbfvrp2[i]->name).c_str())];
        else bbfvrp_cost2 += adjacency2[atoi((bbfvrp2[i - 1]->name).c_str())][atoi((bbfvrp2[i]->name).c_str())];
        bbfvrp_cost2 += bbfvrp2[i]->visitTime;
    }
    bbfvrp_cost2 += adjacency2[atoi((bbfvrp2[bbfvrp2.size() - 1]->name).c_str())][0];
    cout << "0" << endl;
    cout << "gain " << bbfvrp_gain2 << " cost " << bbfvrp_cost2 << endl;

}

void testTime(unsigned int number_tests, unsigned int number_cities) {
    
    double avg_clock_tsp {0};
    double avg_clock_vrp {0};
    double avg_clock_bnb {0};
    double avg_clock_bftsp {0};
    double avg_clock_bfvrp {0};
    double avg_clock_bbftsp {0};
    double avg_clock_bbfvrp {0};
    double avg_clock_bfg {0};
    for (unsigned int i = 0; i < number_tests; i++) {
        TestTime *test = new TestTime(number_cities, 20, 1, 3, 1);
        avg_clock_tsp += test->runTimeTSP();
        avg_clock_vrp += test->runTimeVRP();
        avg_clock_bnb += test->runTimeBnB();
        avg_clock_bftsp += test->runTimeBFTSP();
        avg_clock_bfvrp += test->runTimeBFVRP();
        avg_clock_bbftsp += test->runTimeTSPBF();
        avg_clock_bbfvrp += test->runTimeVRPBF();
        avg_clock_bfg += test->runTimeBFG();
        delete test;
    }
    avg_clock_tsp /= number_tests;
    avg_clock_vrp /= number_tests;
    avg_clock_bnb /= number_tests;
    avg_clock_bftsp /= number_tests;
    avg_clock_bfvrp /= number_tests;
    avg_clock_bbftsp /= number_tests;
    avg_clock_bbfvrp /= number_tests;
    avg_clock_bfg /= number_tests;
    cout << "average clocks greedy TSP " << static_cast<int>(avg_clock_tsp) << endl;
    cout << "average clocks greedy VRP "  << static_cast<int>(avg_clock_vrp) << endl;
    cout << "average clocks branch VRP "  << static_cast<int>(avg_clock_bnb) << endl;
    cout << "average clocks brutef TSP "  << static_cast<int>(avg_clock_bftsp) << endl;
    cout << "average clocks brutef VRP "  << static_cast<int>(avg_clock_bfvrp) << endl;
    cout << "average clocks bfopti TSP "  << static_cast<int>(avg_clock_bbftsp) << endl;
    cout << "average clocks bfopti VRP "  << static_cast<int>(avg_clock_bbfvrp) << endl;
    cout << "average clocks bfgree VRP "  << static_cast<int>(avg_clock_bfg) << endl;
    
}

void testQuality(unsigned int number_tests, unsigned int number_cities) {
    
    double avg_cost_tsp {0};
    double avg_cost_tspbf {0};
    double avg_gain_vrp {0};
    double avg_gain_bnb {0};
    double avg_gain_vrpbf {0};
    for (unsigned int i = 0; i < number_tests; i++) {
        TestTime *test = new TestTime(number_cities, 10, 7, 5, 1);
        vector<double> qualTSP = test->qualityTSP();
        avg_cost_tsp += qualTSP[0];
        avg_cost_tspbf += qualTSP[1];
        vector<double> qualVRP = test->qualityVRP();
        avg_gain_vrp += qualVRP[0];
        avg_gain_bnb += qualVRP[1];
        avg_gain_vrpbf +=qualVRP[2];
        delete test;
    }
    avg_cost_tsp /= number_cities;
    avg_cost_tspbf /= number_cities;
    avg_gain_vrp /= number_cities;
    avg_gain_bnb /= number_cities;
    avg_gain_vrpbf /= number_cities;
    
    cout << "total average cost greedy TSP " << static_cast<int>(avg_cost_tsp) << endl;
    cout << "total average cost brutef TSP " << static_cast<int>(avg_cost_tspbf) << endl;
    cout << "greedy solution is " << round ((avg_cost_tsp - avg_cost_tspbf) * 100 / avg_cost_tspbf) << "% worst" << endl;
    cout << "total average gain greedy VRP " << static_cast<int>(avg_gain_vrp) << endl;
    cout << "total average gain branch VRP " << static_cast<int>(avg_gain_bnb) << endl;
    cout << "total average gain brutef VRP " << static_cast<int>(avg_gain_vrpbf) << endl;
    cout << "greedy solution is " << round ((avg_gain_vrpbf - avg_gain_vrp) * 100 / avg_gain_vrpbf) << "% worst" << endl;
    cout << "branch solution is " << round ((avg_gain_vrpbf - avg_gain_bnb) * 100 / avg_gain_vrpbf) << "% worst" << endl;

}

int main() {
    
    srand (static_cast<int>(time(NULL)));
    
//    testSequanceGenerator(5);
//    cout << endl;
    
    testResult();
    cout << endl;
    
    testTime(1000, 7);
    cout << endl;
    
    testQuality(1000, 7);
    cout << endl;
    
}
