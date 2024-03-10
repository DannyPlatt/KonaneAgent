#ifndef MINIMAXPLAYER
#define MINIMAXPLAYER
#include "KonaneBoard.hpp"

class MiniMaxPlayer {
public:
  char player;
  char opponent;
  int counter;
  MiniMaxPlayer(KonaneBoard, char player);

  vector<int> makeMove(KonaneBoard state);

  vector<int> Decision(KonaneBoard state, int depth);

  int maxVal(KonaneBoard state, int depth);

  int minVal(KonaneBoard state, int depth);

  int evaluate(KonaneBoard state, int multiplier);
};

#endif
