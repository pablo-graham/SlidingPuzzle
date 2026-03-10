//
// Created by Pablo Ruiz on 5/15/25.
//

#include "A_Star.h"

int A_Star::manhattanDistance(const string &board) {
    int distance = 0;

    for(int i = 0; i < board.length(); i++){
        if(board[i] == '0') continue;

        int val = board[i] - '1';

        //distance of each character from its goal
        distance += abs(i/gridSize - val/gridSize) + abs(i%gridSize - val%gridSize);
    }

    return distance;
}

int A_Star::linearConflict(const string &board) {
    // https://www.youtube.com/watch?v=8t3lPD2Qtao
    // Checks num of times a num is blocked from its goal with another number in same row/col that is also blocked from its goal
    int conflict = 0;

    for (int i = 0; i < board.size(); i++) {
        char tile = board[i];
        if (tile == '0') continue;

        int val = tile - '1';

        int currentRow = i / gridSize;
        int currentCol = i % gridSize;

        int goalRow = val / gridSize;
        int goalCol = val % gridSize;

        // Row conflicts
        if (currentRow == goalRow) {
            for (int j = currentCol + 1; j < gridSize; j++) {
                char otherTile = board[currentRow * gridSize + j];

                if (otherTile == '0') continue;

                int otherVal = otherTile - '1';
                int otherGoalRow = otherVal / gridSize;
                int otherGoalCol = otherVal % gridSize;

                if (otherGoalRow == currentRow && otherGoalCol < goalCol) {
                    conflict += 2;
                }
            }
        }

        // Column conflicts
        if (currentCol == goalCol) {
            for (int j = currentRow + 1; j < gridSize; j++) {
                char otherTile = board[j * gridSize + currentCol];
                if (otherTile == '0') continue;

                int otherVal = otherTile - '1';
                int otherGoalRow = otherVal / gridSize;
                int otherGoalCol = otherVal % gridSize;

                if (otherGoalCol == currentCol && otherGoalRow < goalRow) {
                    conflict += 2;
                }
            }
        }
    }

    return conflict;
}

vector<string> A_Star::getNeighbors(const string &board) {
    // all possible combinations to move '0'

    int zero = board.find('0');
    int zeroRow = zero/gridSize, zeroCol = zero % gridSize;

    vector<sf::Vector2i> direction = {{-1, 0}, {1,0}, {0, 1}, {0, -1}};
    ///                                     left          right         up           down

    vector<string> neighbors;

    for(auto dir : direction){
        int newRow = zeroRow + dir.x;
        int newCol = zeroCol + dir.y;

        if(newRow >= 0 && newRow < gridSize && newCol >= 0 && newCol < gridSize){
            int newPos= newRow * gridSize + newCol;
            string newBoard = board;
            swap(newBoard[zero], newBoard[newPos]);
            neighbors.push_back(newBoard);
        }
    }

    return neighbors;
}

void A_Star::solve(const string &start) {
    unordered_map<string, string> cameFrom;        //using to reconst path taken
    unordered_map<string, int> heuristicG;                  //cost per each state

    int statesExplored = 0;

    priority_queue<State, vector<State>, greater<State>> pq;
    ///                                     min sort

    int startHeuristic = manhattanDistance(start) + linearConflict(start);

    //g[start] = 0;
    heuristicG[start] = 0;

    //f[start] = h(start) + g[start];
    pq.push({start, heuristicG[start], startHeuristic, startHeuristic, static_cast<int>(start.find('0'))});
    ///                              g                   h                   f

    //while(set is not empty){
    while (!pq.empty()) {
        cout << "pq is not empty\n";
        //currentVertex = the neighbor with the lowest f value
        State currentVertex = pq.top();
        pq.pop();

        statesExplored++;

        //if(goal is reached){
        if (currentVertex.board == goal) {
            cout << "goal is reached\n";
            solutionPath.clear();

            string state = currentVertex.board;

            while (cameFrom.find(state) != cameFrom.end()) {
                solutionPath.push_back(state);
                state = cameFrom[state];
            }

            solutionPath.push_back(start);

            reverse(solutionPath.begin(), solutionPath.end());

            // Printing steps taken
            int step = 0;
            for (const string &b : solutionPath) {
                cout << "Step " << step++ << ":\n";
                for (int i = 0; i < b.length(); i++) {
                    cout << b[i] << ' ';
                    if ((i + 1) % gridSize == 0)
                        cout << '\n';
                }
                cout << '\n';
            }

            // Prints explored states
            cout << "Explored States:\n";
            int exploredCount = 0;
            for (const auto& entry : heuristicG) {
                cout << "State " << exploredCount++ << ":\n";
                const string &b = entry.first;
                for (int i = 0; i < b.length(); i++) {
                    cout << b[i] << ' ';
                    if ((i + 1) % gridSize == 0)
                        cout << '\n';
                }
                cout << '\n';
            }

            //return path;
            return;
        }

        //loop through all the neighbors of current
        for (const string &neighbor : getNeighbors(currentVertex.board)) {
            //calculate tentative f[neighbore]
            int newG = currentVertex.currentCost + 1;
            int h = manhattanDistance(neighbor) + linearConflict(neighbor);
            int f = newG + h;

            //if(score is better)
            if (heuristicG.find(neighbor) == heuristicG.end() || newG < heuristicG[neighbor]) {
            ///   found new state                                           score is better
                //update g and f
                heuristicG[neighbor] = newG;
                cameFrom[neighbor] = currentVertex.board;

                pq.push({neighbor, newG, h, f, static_cast<int>(neighbor.find('0'))});
            }
        }
    }

    cout << "No solution found\n";
}


