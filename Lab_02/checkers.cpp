#include <bits/stdc++.h>
#include "aux_functions.hpp"

using namespace std;

int board[8][8] = {
  {0, -1, 0, -1, 0, -1, 0, -1},
  {-1, 0, -1, 0, -1, 0, -1, 0},
  {0, -1, 0, -1, 0, -1, 0, -1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 1, 0, 1, 0, 1, 0},
  {0, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0}
};

// Game Setup

bool chooseAlgorithm = 0;     // 0 for minimax, 1 for alpha-beta
bool chooseColor = 0;         // 0 for white, 1 for black

int humanPiece = 1;
int computerPiece = -1;
int maxDepth;

class Node {
  public:
    int bestBoard[8][8];
    int currentBoard[8][8];
    int depth;
    bool minimize;

    // constructor
    Node(int _currentBoard[8][8], int _depth) {
      copyBoard(currentBoard, bestBoard);
      depth = _depth;
      minimize = depth > 2 ? 1 : 0;      
    }

    // minmax implementation
    int minMax() {
      if (depth == maxDepth) {
        return evaluateFunction(currentBoard);
      }
    }
};


int main() {

  cout << "sintaxys test" << endl;

  return 0;
}