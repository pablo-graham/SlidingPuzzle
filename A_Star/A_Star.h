//
// Created by Pablo Ruiz on 5/15/25.
//

#ifndef MALENATEST_A_STAR_H
#define MALENATEST_A_STAR_H
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#include "Malena/common.hpp"


#include "../State/State.h"


using namespace std;
class A_Star{
public:
    int manhattanDistance(const string& board);             ///Heuristic
    int linearConflict(const string& board);

    vector<string> getNeighbors(const string& board);

    void solve(const string& start);                        ///A*

    vector<string> getSolutionPath(){ return solutionPath; }


private:
    int gridSize = 3;
    const string goal = "123456780";

    vector<string> solutionPath;

};
/*
psuedo code:
A*(start){
    //create a set and add start states
    ///vertex = node
    //h is heuristic function, g is how many steps from start

    g[start] = 0;
    f[start] = h(start) + g[start];

    while(set is not empty){
        currentVertex = the neighbor with the lowest f value

        if(goal is reached){
            return path;
        }

        loop through all the neighbors of current

            calculate tentative f[neighbore]

            if(score is better){
            update g and f
            }
            if(neighbor is not in the set){
            add to the set

        }
    }
}
 */

#endif //MALENATEST_A_STAR_H
