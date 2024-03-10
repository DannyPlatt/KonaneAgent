#ifndef BOARDCLASS
#define BOARDCLASS

#include <bitset>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define BOARDBITS 64
#define BOARDDIM BOARDBITS / 8
typedef bitset<BOARDBITS> Unit;

class KonaneBoard {

public:
  Unit availBoard, playerBoard;
  char playerChar, opponentChar;
  vector<vector<int>> availableMoves;

  KonaneBoard(Unit boardA, Unit boardP, char playerCharInput); // Constructor

  void printBoard();

  void printBoardBits();

  void getAvailMoves(char player);

  void availableMovesY(int index, char player);

  void availableMovesX(int index, char player);

  bool checkEmpty(int index);

  char checkPlayer(int index);

  void movePlayer(int index, int index2, char player);

  void removePlayer(int index);

  void placePlayer(int index, char player);

  void getUserInput(char player);

  vector<KonaneBoard> generateChildren();

  int randomMove(char player);
};

#endif // !BOARDCLASS
