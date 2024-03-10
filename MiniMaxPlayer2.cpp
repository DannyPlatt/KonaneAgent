/* Program: MiniMaxPlayer2.cpp
 * Purpose: MiniMaxPlayer2 uses miniMax algorithm to determin best move
 * Author: Danny Platt
 * Last Edited: 10/03/24 [DD/MM/YY]
 */

#include "MiniMaxPlayer2.hpp"
#define DEPTH 3

MiniMaxPlayer2::MiniMaxPlayer2(KonaneBoard board, char Player)
    : player(Player), counter(0) {
  if (player == 'B')
    opponent = 'W';
  else
    opponent = 'B';
}

vector<int> MiniMaxPlayer2::makeMove(KonaneBoard state) {
  // Purpose: Handle first move and call decision
  // Parameters: state: Board state to make the move from
  // RETURNS: vector containing move idicies{StartIndex, EndIndex}
  //          NOTE: For first move, returnMove[1] == -1
  vector<int> returnMove = {};
  // set board player
  state.playerChar = player;
  state.opponentChar = opponent;

  // Check for First Move case
  int count = 0;
  for (size_t i = 0; i < BOARDBITS; i++) {
    if (state.checkEmpty(i))
      count += 1;
  }
  if (count < 2) { // play first move
    if (player == 'B')
      returnMove.push_back(36); // TODO: HardCoded
    else
      returnMove.push_back(35); // TODO: HardCoded
    returnMove.push_back(-1);   // Add -1 to indicate first move

  } else { // Determin best move
    state.getAvailMoves(player);
    if (state.availableMoves.size() == 0) {
      returnMove.push_back(-1);
      return returnMove;
    }
    returnMove = Decision(state, DEPTH);
  }
  cout << "MiniMax Counter: " << counter << endl;
  return returnMove;
}

vector<int> MiniMaxPlayer2::Decision(KonaneBoard state, int depth) {
  // Purpose: Iteratet through the direct possible children
  // Calls: minVal
  // RETURNS: vector containing move idicies
  //          vector returns empty if no children can be found

  // SETUP
  // getAvailMoves(playerChar);
  int value = 0;
  int bestMoveValue = 0;
  vector<int> moveChoice = {};
  // children.size() is equal to 0?
  vector<KonaneBoard> children = state.generateChildren();
  if (children.size() == 0) {
    return moveChoice;
  }
  int bestMoveIndex = 0;
  KonaneBoard bestMove = children[0]; // maybe not needed
  for (size_t i = 0; i < children.size(); i++) {
    value = minVal(children[i], depth - 1);
    if (value > bestMoveValue) {
      bestMoveIndex = i;
      bestMoveValue = value;
    }
  }

  // cout << "in Decision:" << endl; // TODO DELETE
  counter++;
  return state.availableMoves[bestMoveIndex];
}

int MiniMaxPlayer2::maxVal(KonaneBoard state, int depth) {
  // Purpose: determin the heighest score possible from current board
  // Calls: minVal
  // RETURNS: value: the value of the child with the highest score

  vector<KonaneBoard> children = state.generateChildren();
  // Recursive end point, (terminal node)
  if (children.size() == 0 || depth == 0)
    return evaluate(state, 1);
  int value = -10000;
  // find the child with the heighest evaluation value
  for (size_t i = 0; i < children.size(); i++) {
    value = max(value, minVal(children[i], depth - 1));
  }
  counter++;
  return value;
}

int MiniMaxPlayer2::minVal(KonaneBoard state, int depth) {
  // Purpose: determin the lowest score possible from current board
  // Calls: minVal
  // RETURNS: value: the value of the child with the lowest score

  vector<KonaneBoard> children = state.generateChildren();
  // Check if terminal node
  if (children.size() == 0 || depth == 0)
    return evaluate(state, -1);
  // Intial value to compare against
  int value = 10000;
  // find the child with smallest evaluation value
  for (size_t i = 0; i < children.size(); i++) {
    value = min(value, maxVal(children[i], depth - 1));
  }
  counter++;
  return value;
}

int MiniMaxPlayer2::evaluate(KonaneBoard state, int multiplier) {
  // Purpose: Determin evaluation function score for board state
  // Parameters: multiplier: 1 for max, -1 for min
  // Returns: Evaluation function score

  state.getAvailMoves(player);
  int terminal = 0;
  if (state.availableMoves.size() == 0)
    terminal += -1000;

  // Total up number of tiles for each player
  int playerScore = 0, opponentScore = 0;
  for (size_t i = 0; i < BOARDBITS; i++) {
    if (state.checkPlayer(i) == player)
      playerScore++;
    if (state.checkPlayer(i) == opponent)
      opponentScore++;
  }
  return (state.availableMoves.size() + playerScore - opponentScore +
          terminal) *
         multiplier;
}
