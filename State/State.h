//
// Created by Pablo Ruiz on 5/17/25.
//

#ifndef MALENATEST_STATE_H
#define MALENATEST_STATE_H

#include "Malena/common.hpp"
#include <iostream>
#include <string>

using namespace std;
struct State{
    string board;
    vector<ml::RectangleButton> boardBTN;

    int currentCost, estimateCost, totalCost, blankPos;
    ///   g(n)          h(n)          f(n)


    bool operator>(const State& other) const {
        return totalCost > other.totalCost;
    }

    friend ostream& operator <<(ostream& outs, const State state){

        return outs;
    }

    State(){}
    State(const string& b, int cc, int ec, int tc, int blank) : board(b), currentCost(cc), estimateCost(ec), totalCost(tc), blankPos(blank) {}

};


#endif //MALENATEST_STATE_H
