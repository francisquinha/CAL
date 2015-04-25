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
//    srand (static_cast<int>(time(NULL)));
//    TestBNB *test = new TestBNB(10000, 20, 1, 3, 1);
//    cout << test->runTime() << endl;
/*    vector<vector<double> > adjacency1 = {
        {0, 2, 3, 1},
        {2, 2, 5, 2},
        {3, 5, 3, 3},
        {1, 2, 3, 2}
    };
    vector<double> preference1 = {0, 7, 8, 5};
    double limit1 = 15;
    vector<unsigned int> tsp1 = {};
    double tsp_cost1 {0};
    vector<unsigned int> vrp1 = {};
    double vrp_gain1 {0};
    double vrp_cost1 {0};
    GreedyApproxTSP(adjacency1, tsp1, tsp_cost1);
    for (unsigned int i = 0; i < tsp1.size(); i++) {
        cout << tsp1[i] << " -> ";
    }
    cout << tsp1[0] << endl;
    cout << tsp_cost1 << endl;
    GreedyApproxVRP(adjacency1, preference1, limit1, vrp1, vrp_gain1, vrp_cost1);
    for (unsigned int i = 0; i < vrp1.size(); i++) {
        cout << vrp1[i] << " -> ";
    }
    cout << vrp1[0] << endl;
    cout << vrp_gain1 << " " << vrp_cost1 << endl;
    vector<vector<double> > adjacency2 = {
        {0, 2, 4, 1, 3},
        {2,	4, 5, 3, 2},
        {4,	5, 4, 3, 6},
        {1,	3, 3, 3, 7},
        {3,	2, 6, 7, 6}
    };
    vector<double> preference2 = {0, 2, 7, 5, 3};
    double limit2 = 25;
    vector<unsigned int> tsp2 = {};
    double tsp_cost2 {0};
    vector<unsigned int> vrp2 = {};
    double vrp_gain2 {0};
    double vrp_cost2 {0};
    GreedyApproxTSP(adjacency2, tsp2, tsp_cost2);
    for (unsigned int i = 0; i < tsp2.size(); i++) {
        cout << tsp2[i] << " -> ";
    }
    cout << tsp2[0] << endl;
    cout << tsp_cost2 << endl;
    GreedyApproxVRP(adjacency2, preference2, limit2, vrp2, vrp_gain2, vrp_cost2);
    for (unsigned int i = 0; i < vrp2.size(); i++) {
        cout << vrp2[i] << " -> ";
    }
    cout << vrp2[0] << endl;
    cout << vrp_gain2 << " " << vrp_cost2 << endl;*/
    
/*    unsigned int number_tests = 1000;
    
    srand (static_cast<int>(time(NULL)));
    double avg_clock_tsp {0};
    double avg_clock_vrp {0};
    for (unsigned int i = 0; i < number_tests; i++) {
        TestGreedy *test = new TestGreedy(900, 20, 1, 3, 1);
        avg_clock_tsp += test->runTimeTSP();
        avg_clock_vrp += test->runTimeVRP();
        delete test;
    }
    avg_clock_tsp /= number_tests;
    avg_clock_vrp /= number_tests;
    cout << avg_clock_tsp << "/" << avg_clock_vrp << endl;*/
    
    srand (static_cast<int>(time(NULL)));
    
    unsigned int number_tests = 1000;
    
    unsigned int number_cities = 30;
     
    double avg_clock_tsp {0};
    double avg_clock_vrp {0};
    double avg_clock_bf {0};
    double avg_clock_bfg {0};
    double avg_clock_bnb {0};
    for (unsigned int i = 0; i < number_tests; i++) {
        TestTime *test = new TestTime(number_cities, 20, 1, 3, 1);
        avg_clock_tsp += test->runTimeTSP();
        avg_clock_vrp += test->runTimeVRP();
        avg_clock_bf += test->runTimeTSP();
        avg_clock_bfg += test->runTimeVRP();
        avg_clock_bnb += test->runTimeBnB();
        delete test;
    }
    avg_clock_tsp /= number_tests;
    avg_clock_vrp /= number_tests;
    avg_clock_bf /= number_tests;
    avg_clock_bfg /= number_tests;
    avg_clock_bnb /= number_tests;
    cout << avg_clock_tsp << "/" << avg_clock_vrp << "/" << avg_clock_bf << "/" << avg_clock_bfg << "/" << avg_clock_bnb << endl;
    

}
