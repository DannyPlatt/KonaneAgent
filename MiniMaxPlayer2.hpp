#ifndef MINIMAXPLAYER2
#define MINIMAXPLAYER2
#include "KonaneBoard.hpp"

class MiniMaxPlayer2 {
public:
  char player;
  char opponent;
  int counter;
  MiniMaxPlayer2(KonaneBoard, char player);

  vector<int> makeMove(KonaneBoard state);

  vector<int> Decision(KonaneBoard state, int depth);

  int maxVal(KonaneBoard state, int depth);

  int minVal(KonaneBoard state, int depth);

  int evaluate(KonaneBoard state, int multiplier);
};

#endif
