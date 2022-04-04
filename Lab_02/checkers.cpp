#include <bits/stdc++.h>
#include "aux_functions.hpp"

using namespace std;

#define INF 12345

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
bool chooseAlgorithm = 0;     // 0 for minimax, 1 for alphxbeta
bool chooseColor = 0;         // 0 for white, 1 for black

int humanPiece = 1;
int computerPiece = -1;
int maxDepth;

pair<int, int> humanOptions[2] = {
  {-1, -1},
  {-1, 1}
};

pair<int, int> computerOptions[2] = {
  {1, -1},
  {1, 1}
};

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
      if(depth == maxDepth) {
        return evaluateFunction(currentBoard);
      }
      int bestScore = minimize ? INF : -INF;
      int humanScore = minimize ? 1 : -1;
      pair<int, int>* options = minimize ? humanOptions : computerOptions;

      for (int i = 0; i <= 7 ; ++i){
        for (int j = 0; j <= 7 ; ++j){
          if(currentBoard[i][j] == humanScore){
            for (int k = 0; k <= 1 ; ++k){
              int x = i + options[k].first;
              int y = j + options[k].second;

              if (x >= 0 && x <= 7 && y >= 0 && y <= 7 && currentBoard[x][y] == 0) {
                // simple move
                currentBoard[i][j] = 0;
                currentBoard[x][y] = humanScore;
                Node child(currentBoard, depth + 1);
                int score = child.minMax();

                if (minimize && score < bestScore) {
                  bestScore = score;
                  copyBoard(bestBoard, currentBoard);
                }

                if (!minimize && score > bestScore) {
                  bestScore = score;
                  copyBoard(bestBoard, currentBoard);
                }

                currentBoard[i][j] = humanScore;
                currentBoard[x][y] = 0;
              }

              x += options[k].first;
              y += options[k].second;

              if (x >= 0 && x <= 7 && y >= 0 && y <= 7 && currentBoard[x][y] == 0 &&
                  currentBoard[x-options[k].first][y-options[k].second] == -humanScore) {
                // eat a piece
                currentBoard[i][j] = 0;
                currentBoard[x-options[k].first][y-options[k].second] = 0;
                currentBoard[x][y] = humanScore;
                Node child(currentBoard, depth + 1);
                int score = child.minMax();

                if (minimize && score < bestScore) {
                  bestScore = score;
                  copyBoard(bestBoard, currentBoard);
                }

                if (!minimize && score > bestScore) {
                  bestScore = score;
                  copyBoard(bestBoard, currentBoard);
                }

                currentBoard[i][j] = humanScore;
                currentBoard[x-options[k].first][y-options[k].second] = -humanScore;
                currentBoard[x][y] = 0;
              }
            }
          }
        }
      }
      return bestScore;
    }
};



int main() {
  Node A(board, 3);



  cout << A.minMax() << endl;

  return 0;
}