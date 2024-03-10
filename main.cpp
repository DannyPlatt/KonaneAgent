/* Program: main.cpp
 * Purpose: Hosts Konane game
 * Author: Danny Platt
 * Last Edited: 10/03/24 [DD/MM/YY]
 */

#include "KonaneBoard.hpp"
#include "MiniMaxPlayer.hpp"
#include "MiniMaxPlayer2.hpp"

int main() {
  // Purpose: Host Konane Game

  Unit boardA = 0xFFFFFFFFFFFFFFFF;
  Unit boardP = 0x55aa55aa55aa55aa;

  KonaneBoard boardBlack = KonaneBoard(boardA, boardP, 'B');
  MiniMaxPlayer2 BlackMiniMax =
      MiniMaxPlayer2(KonaneBoard(boardA, boardP, 'B'), 'B');
  MiniMaxPlayer WhiteMiniMax =
      MiniMaxPlayer(KonaneBoard(boardA, boardP, 'W'), 'W');
  vector<int> whiteMove = {};
  vector<int> blackMove = {};

  while (1) {

    // if (boardBlack.randomMove('B')) {
    //   cout << "White Wins!" << endl;
    //   break;
    // }

    // Black makes move:
    cout << "Black Move:" << endl;
    blackMove = BlackMiniMax.makeMove(boardBlack);
    if (blackMove[0] == -1) { // Check endgame state
      cout << "White Wins" << endl;
      break;
    } else if (blackMove[1] == -1) // Check for first move
      boardBlack.removePlayer(blackMove[0]);
    else
      boardBlack.movePlayer(blackMove[0], blackMove[1], 'B');
    boardBlack.printBoard();

    // White makes move:
    cout << "White Move:" << endl;
    whiteMove = WhiteMiniMax.makeMove(boardBlack);
    if (whiteMove[0] == -1) {
      cout << "Black Wins" << endl;
      break;
    } else if (whiteMove[1] == -1) // Check for first move
      boardBlack.removePlayer(whiteMove[0]);
    else
      boardBlack.movePlayer(whiteMove[0], whiteMove[1], 'W');
    boardBlack.printBoard();
  }

  return 0;
}
