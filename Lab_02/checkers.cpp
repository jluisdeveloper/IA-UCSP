#include <iostream>
#include "aux_functions.hpp"

using namespace std;

#define TOTAL_PIECES 24
#define INF 12345
#define EMPTY_SQUARE 0

/*int board[8][8] = {
  {0, -1, 0, -1, 0, -1, 0, -1},
  {-1, 0, -1, 0, -1, 0, -1, 0},
  {0, -1, 0, -1, 0, -1, 0, -1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 1, 0, 1, 0, 1, 0},
  {0, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0}
};*/

int board[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, -1, 0, -1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 1, 0, 1, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

pair<int, int> pieces[TOTAL_PIECES];


bool chooseColor;
bool chooseAlgorithm;

int humanPiece = 1;
int computerPiece = -1;
int maxDepth;

pair<int, int> computerOptions[2] = {{1, -1}, {1, 1}};
pair<int, int> humanOptions[2] = {{-1, -1}, {-1, 1}};

struct Node {
  int bestBoard[8][8];
  int currentBoard[8][8];
  int depth;
  bool minimize;

  Node(int c[8][8],  int d) : depth(d) {
    copyBoard(currentBoard, c);
    minimize = depth > 2 ? 1 : 0;
  }

  int minMax() {
    if (depth == maxDepth)
      return evaluateFunction(currentBoard);

    // recursion
    int best = minimize ? INF : -INF;
    int player = minimize ? 1 : -1;
    pair<int, int>* options = minimize ? humanOptions : computerOptions;

    // visit children
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (currentBoard[i][j] == player) {
          for (int k = 0; k < 2; ++k) {
            int x = i + options[k].first;
            int y = j + options[k].second;

            if (x >= 0 && x < 8 && y >= 0 && y < 8 && currentBoard[x][y] == 0) {
              // simple move
              currentBoard[i][j] = 0;
              currentBoard[x][y] = player;
              Node child(currentBoard, depth + 1);
              int score = child.minMax();

              if (minimize && score < best) {
                best = score;
                copyBoard(bestBoard, currentBoard);
              }

              if (!minimize && score > best) {
                best = score;
                copyBoard(bestBoard, currentBoard);
              }

              currentBoard[i][j] = player;
              currentBoard[x][y] = 0;
            }

            x += options[k].first;
            y += options[k].second;

            if (x >= 0 && x < 8 && y >= 0 && y < 8 && currentBoard[x][y] == 0 && currentBoard[x-options[k].first][y-options[k].second] == -player) {

              currentBoard[i][j] = 0;
              currentBoard[x-options[k].first][y-options[k].second] = 0;
              currentBoard[x][y] = player;
              Node child(currentBoard, depth + 1);
              int score = child.minMax();

              if (minimize && score < best) {
                best = score;
                copyBoard(bestBoard, currentBoard);
              }

              if (!minimize && score > best) {
                best = score;
                copyBoard(bestBoard, currentBoard);
              }

              currentBoard[i][j] = player;
              currentBoard[x-options[k].first][y-options[k].second] = -player;
              currentBoard[x][y] = 0;
            }
          }
        }
      }
    }
    return best;
  }

  int alphaBeta() {
    // implementar poda mas adelante
    return 0;
  }
};

void loadPosition() {
  int k = 0;
  int square, y;

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      square = board[i][j];

      if (square == EMPTY_SQUARE)
        continue;

      if (chooseColor == 0)
        y = (square > 0) ? 1 : 0;
      else
        y = (square > 0) ? 0 : 1;

      pieces[k] = {j, i};
      ++k;
    }
  }
}

bool invalidMove(pair<int,int> to) {
  if (to.first >= 8 || to.first < 0 ||
      to.second >= 8 || to.second < 0)
    return true;

  for (int i = 0; i < TOTAL_PIECES; ++i) {
    if (pieces[i] == to)
      return true;
  }

  return false;
}

enum Direction {
  Right,
  Left,
  JumpRight,
  JumpLeft,
  Invalid
};

Direction getOrientation(pair<int,int> from, pair<int,int> to) {
  pair<int,int> movementVector = {to.first - from.first, to.second - from.second};

  if (movementVector.first == 1 && movementVector.second == -1)
    return Right;

  if (movementVector.first == 2 && movementVector.second == -2)
    return JumpRight;

  if (movementVector.first == -1 && movementVector.second == -1)
    return Left;

  if (movementVector.first == -2 && movementVector.second == -2)
    return JumpLeft;

  return Invalid;
}

// test function
void printBoard() {
  int rr, cc, pp;
    
  cout<< "\n\n";
  cout<<("   0   1   2   3   4   5   6   7\n");
  cout<<(" +---.---.---.---.---.---.---.---+\n");

  for (rr = 0; rr < 8; ++rr)
  {
      cout<<rr<<"|";
      for (cc = 0; cc < 8; ++cc)
      {
          if (board[rr][cc] == 1)
              cout << " # |";

          if (board[rr][cc] == -1)
              cout << " $ |";

          if (board[rr][cc] == 0)
              cout << "   |";
      }
      cout<<rr<<"\n";
      cout<<(" +---.---.---.---.---.---.---.---+\n");
  }

  cout<<("   0   1   2   3   4   5   6   7\n");
  cout<<"\n\n";
}

bool movePiece(pair<int, int> from, pair<int, int> to) {
  if (invalidMove(to))
    return false;

  Direction direction = getOrientation(from, to);

  if (direction == Invalid)
    return false;

  if (direction == JumpLeft || direction == JumpRight) {
    pair<int, int>  middleSquare = {(from.first + to.first) / 2, (from.second + to.second) / 2};
    bool capturedEnemy = false;

    for (int i = 0; i < TOTAL_PIECES; ++i) {
      const pair<int, int>& piecePosition = pieces[i];
      int& square = board[piecePosition.second][piecePosition.first];

      // printBoard();

      if (piecePosition == middleSquare
          && square == computerPiece) {
        square = 0;
        capturedEnemy = true;
      }
    }

    if (!capturedEnemy)
      return false;
  }

  return true;
}

void getWinner() {
  int result = evaluateFunction(board);

  if (result < 0)
    cout << "\nHUMAN WINNER\n" << endl;
  else if (result == 0)
    cout << "\nTIED, NO WINNERS\n" << endl;
  else
    cout << "\nCOMPUTER WINNER\n" << endl;
}

bool calculateMovement() {
  Node root(board, 0);
  int result;

  if (chooseAlgorithm == 0)
    result = root.minMax();
  else
    result = root.alphaBeta();

  if (result == -INF) {
    getWinner();
    return false;
  }
  
  copyBoard(board, root.bestBoard);
  return true;
}

bool optionsHuman() {
  pair<int, int>* options = humanOptions;

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (board[i][j] == humanPiece) {
        for (int k = 0; k < 2; ++k) {
          int x = i + options[k].first;
          int b = j + options[k].second;

          if (x >= 0 && x < 8 && b >= 0 && b < 8 && board[x][b] == 0)
            return true;

          x += options[k].first;
          b += options[k].second;

          if (x >= 0 && x < 8 && b >= 0 && b < 8 && board[x][b] == 0 && board[x-options[k].first][b-options[k].second] == computerPiece)
            return true;
        }
      }
    }
  }

  return false;
}

int main() {
  cout << "\n\tDAMAS Go..!! Go..!!\n\n";
  int Player ;
  cout << "Quien empieza el juego? \n 0 = computadora,  1 = Player: ";
  cin >> Player;
  bool turn = 0;

  cout << "minMax algorithm loaded!" << endl;
  chooseAlgorithm = 0;

  cout << "depth (0 - 12) : ";
  cin >> maxDepth;

  loadPosition();
  printBoard();

  bool movingPiece = false;
  float deltaX, deltaY;
  pair<int, int> oldPiecePosition, newPiecePosition;
  int currentPiece = 0;
  bool keepGoing = true;

  pair<int, int> move;
  pair<int, int> newMove;
  if(!Player){
    keepGoing = calculateMovement();
    loadPosition();
    printBoard();
  }

  while (keepGoing == true) {
    cout << "enter the position of the part to be moved (columna , fila)" << endl;
    cin >> move.first >> move.second;
    // checamos si la pieza elegida es del jugador
    if (board[move.second][move.first] == humanPiece ){
      movingPiece = true;
      oldPiecePosition = move;
    }else {
      cout << "it's not your piece " << endl;
    }

    if (movingPiece) {
      movingPiece = false;

      cout << "enter target position (columna , fila)" << endl;
      cin >> newMove.first >> newMove.second;

      newPiecePosition = newMove;

      if (!movePiece(oldPiecePosition, newPiecePosition))
        pieces[currentPiece] = (oldPiecePosition);
      else {
        pieces[currentPiece] = newPiecePosition;

        board[oldPiecePosition.second][oldPiecePosition.first] = 0;
        board[newMove.second][newMove.first] = humanPiece;

      turn ^= 1;
      }
    }   
    printBoard();

    if (turn && keepGoing) {
      keepGoing = calculateMovement();
      loadPosition();
      turn ^= 1;
      printBoard();
    }

    if (!optionsHuman() && keepGoing) {
      getWinner();
      keepGoing = false;
    }
  }
  return 0;
}
