
void copyBoard(int originalBoard[8][8], int newBoard[8][8]) {
  for (int i = 0; i <= 7; i++) {
    for (int j = 0; j <= 7; j++) {
      originalBoard[i][j] = newBoard[i][j];
    }
  }
}

int evaluateFunction(int board[8][8]) {
  int score = 0;
  for (int i = 0; i <= 7; i++) {
    for (int j = 0; j <= 7; j++) {
      score += -board[i][j];
    }
  }
  return score;
}

