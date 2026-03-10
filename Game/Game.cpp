//
// Created by Pablo Ruiz on 5/15/25.
//

#include "Game.h"
#include "Malena/Utilities/TextureSlicer.h"
#include <ctime>

Game::Game() : Application(sf::VideoMode({720, 720}, 32), "Sliding Puzzle", *this), gridSize(3), gridBoard(sf::Vector2u(3, 3)) {
    gridBoard.setSpacing(0);

    boardStr = DEFAULT_BOARD;
    chosenPic = dogFileNames[1];

    setBoard();

    srand(time(0));
}

Game::Game(int boardSize) : Application(sf::VideoMode({720, 720}, 32), "Sliding Puzzle", *this), gridSize(boardSize), gridBoard(sf::Vector2u(boardSize, boardSize)){
    gridBoard.setSpacing(0);
    setDefaultBoard();

}

void Game::randomizeBoard() {
    chosenPic = dogFileNames[rand() % 5];

    // Randomizes board and checks if its valid and then it's also not the default board
    do {
        int randTimes = rand() % (boardStr.length() - 1);
        for(int i = 0; i < randTimes; i++){
            int rand1 = rand() % boardStr.length(), rand2 = rand() % boardStr.length();

            swap(boardStr[rand1], boardStr[rand2]);
        }
    } while(validBoard(boardStr) && boardStr != DEFAULT_BOARD);


    texture.loadFromFile(chosenPic);
    ml::ImageRects rects = ml::TextureSlicer::getImageRects(texture, 3, 3);

    for(int i = 0; i < boardStr.length(); i++){
        myBoard[i]->c = boardStr[i];
        myBoard[i]->setSize({125.f, 125.f});
        sf::IntRect intRect;

        if(boardStr[i] == '0'){
            myBoard[i]->setFillColor(sf::Color::White);
            myBoard[i]->setTexture(nullptr);
        }else{
            intRect = rects.getIntRect((boardStr[i] - '1') / 3, (boardStr[i] - '1') % 3);
            myBoard[i]->setTextureRect(intRect);
            myBoard[i]->setTexture(&texture);
        }
    }

}

bool Game::validBoard(string tempBoard) {
    int inverse = 0;
    for(int i = 0; i < tempBoard.length(); i++){
        if(tempBoard[i] == '0')
            continue;

        for(int j = i + 1; j < tempBoard.length(); j++){
            if(tempBoard[j] == '0')
                continue;

            if(tempBoard[i] > tempBoard[j])
                inverse++;
        }
    }

    if(inverse % 2 != 0){
        return true;
    }
    return false;
}

void Game::setDefaultBoard() {
    texture.loadFromFile(chosenPic);
    ml::ImageRects rects = ml::TextureSlicer::getImageRects(texture, 3, 3);

    for(int i = 0; i < DEFAULT_BOARD.length(); i++){
        Rect* sq = nullptr;

        sq = new Rect;
        sq->c = DEFAULT_BOARD[i];
        sq->setSize({125.f, 125.f});
        sf::IntRect intRect;

        if(DEFAULT_BOARD[i] == '0'){
            sq->setFillColor(sf::Color::White);
            sq->setTexture(nullptr);
        }else{
            intRect = rects.getIntRect(i / 3, i % 3);
            sq->setTextureRect(intRect);
            sq->setTexture(&texture);
        }

        gridBoard.addComponent(*sq);
        myBoard.push_back(sq);
    }

}

void Game::setBoard() {
    texture.loadFromFile(chosenPic);
    ml::ImageRects rects = ml::TextureSlicer::getImageRects(texture, 3, 3);

    for(int i = 0; i < boardStr.length(); i++){
        Rect* sq = nullptr;

        sq = new Rect;
        sq->c = boardStr[i];
        sq->setSize({125.f, 125.f});
        sf::IntRect intRect;

        if(boardStr[i] == '0'){
            sq->setFillColor(sf::Color::White);
            sq->setTexture(nullptr);
        }else{
            intRect = rects.getIntRect((boardStr[i] - '1') / 3, (boardStr[i] - '1') % 3);
            sq->setTextureRect(intRect);
            sq->setTexture(&texture);
        }


        gridBoard.addComponent(*sq);
        myBoard.push_back(sq);
    }
}

void Game::runSolver() {
    //cout << "runSolver ran\n";
    A_Star solver;
    solver.solve(boardStr);
    ml::ImageRects rects = ml::TextureSlicer::getImageRects(texture, 3, 3);

    for (const auto& state : solver.getSolutionPath()){
        ml::Grid tempGrid(sf::Vector2u(gridSize, gridSize));
        tempGrid.setSpacing(0);

        for (int i = 0; i < state.length(); i++){
            Rect* sq = new Rect;
            sq->c = state[i];
            sq->setSize({125.f, 125.f});

            if (state[i] == '0'){
                sq->setFillColor(sf::Color::White);
                sq->setTexture(nullptr);
            } else{
                intRect = rects.getIntRect((state[i] - '1') / 3, (state[i] - '1') % 3);
                sq->setTextureRect(intRect);
                sq->setTexture(&texture);
            }
            tempGrid.addComponent(*sq);
        }
        steps.push(tempGrid);
    }
}


void Game::initialization() {
    solveBtn.setSize({200, 75});
    solveBtn.setFillColor(sf::Color(0, 102, 204));
    solveBtn.setPosition({450, 125});
    solveBtn.setString("SOLVE");
    solveBtn.setState(ml::Stateful::CLICKED, false);

    solveBtn.bottom(randBtn, 20);

    randBtn.setSize({200, 75});
    randBtn.setFillColor(sf::Color(0, 102, 204));
    randBtn.setString("RANDOMIZE");
    randBtn.setState(ml::Stateful::CLICKED, false);



    addComponent(gridBoard);
    addComponent(solveBtn);
    addComponent(randBtn);
}

void Game::registerEvents() {
    solveBtn.onClick([this](){
        if(!solveBtn.checkState(ml::Stateful::CLICKED))
            runSolver();

        solveBtn.setState(ml::Stateful::CLICKED, true);

    });

    randBtn.onClick([this](){
        //cout << "randBTN clicked\n";
        if(!randBtn.checkState(ml::Stateful::CLICKED))
            randomizeBoard();
        randBtn.setState(ml::Stateful::CLICKED, true);
    });


    ///print solve
    onUpdate([this]() {

        if(steps.empty()){
            solveBtn.setState(ml::Stateful::CLICKED, false);
            randBtn.setState(ml::Stateful::CLICKED, false);

        }
        //cout << "onUpdate() called\n";
        static sf::Clock clock;
        if (clock.getElapsedTime().asSeconds() > .25 && !steps.empty()) {
            //cout << "reg events called\n";
            gridBoard = steps.front();
            addComponent(gridBoard);

            steps.pop();
            clock.restart();
        }
    });


}