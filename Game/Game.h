//
// Created by Pablo Ruiz on 5/15/25.
//

#ifndef SLIDINGPUZZLE_GAME_H
#define SLIDINGPUZZLE_GAME_H
#include "Malena/common.hpp"
#include <iostream>
#include <cstdlib>
#include "../A_Star/A_Star.h"

struct Rect : public ml::RectangleButton{
    char c;
};

using namespace std;
class Game : public ml::Application{
public:
    Game();
    Game(int boardSize);

    void setDefaultBoard();
    void setBoard();
    void randomizeBoard();
    bool validBoard(string tempBoard);

    void runSolver();

private:
    int gridSize;

    ml::RectangleButton solveBtn, randBtn;

    const string DEFAULT_BOARD = "123456780";
    string boardStr;

    ml::Grid gridBoard;
    vector<Rect*> myBoard;

    queue<ml::Grid> steps;

    vector<string> dogFileNames = {"/Users/pabloruiz/CLionProjects/SlidingPuzzle/Game/doggy pics/4becd47c-5d53-42d2-aac4-5c3da96e700d.jpg",
                                   "/Users/pabloruiz/CLionProjects/SlidingPuzzle/Game/doggy pics/83aa7798-2a6c-40c9-8c56-2d1a8fc1c2a1.jpg",
                                   "/Users/pabloruiz/CLionProjects/SlidingPuzzle/Game/doggy pics/917a1821-a2bf-415d-9737-fec3df73927d.jpg",
                                   "/Users/pabloruiz/CLionProjects/SlidingPuzzle/Game/doggy pics/c52bc728-2731-4721-b320-b6b713a88768.jpg",
                                   "/Users/pabloruiz/CLionProjects/SlidingPuzzle/Game/doggy pics/eca54581-0011-47e6-984b-a32963231512.jpg"};
    string chosenPic;

    sf::Texture texture;
    sf::IntRect intRect;


    void initialization() override;
    void registerEvents() override;
    void update();
};


#endif //SLIDINGPUZZLE_GAME_H
