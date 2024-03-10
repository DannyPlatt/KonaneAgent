/* Program: KonaneBoard.cpp
 * Purpose: The KonaneBoard object hosts a KonaneBoard
 * Author: Danny Platt
 * Last Edited: 10/03/24 [DD/MM/YY]
 */

#include "KonaneBoard.hpp"

KonaneBoard::KonaneBoard(Unit boardA, Unit boardP, char playerCharInput)
    : availBoard(boardA), playerBoard(boardP), playerChar(playerCharInput),
      opponentChar('\0'), availableMoves{} {
  if (playerChar == 'B')
    opponentChar = 'W';
  else
    opponentChar = 'B';
}

void KonaneBoard::printBoard() {
  // Purpose: print the user view of the board

  int boardDim = BOARDDIM; // for some reason, BOARDDIM has problems when not
                           // called first
  cout << "  A|B|C|D|E|F|G|H\n";
  for (int i = 0; i < BOARDBITS; i++) {
    if ((i) % boardDim == 0)
      printf("%d ", 8 - i / 8);

    cout << checkPlayer(i) << " ";
    if ((i + 1) % boardDim == 0)
      printf("%d\n", 8 - i / 8);
  }
  cout << "  A|B|C|D|E|F|G|H" << endl;
  printf("----------------------------\n");
}

void KonaneBoard::printBoardBits() {
  // Print the playerBoard and availBoard in their bit forms

  printf("-------- playerBoard -----------\n");
  int boardDim = BOARDDIM;
  for (size_t i = 0; i < BOARDBITS; i++) {
    cout << playerBoard[i] << " ";
    if (((i + 1) % boardDim) == 0)
      printf("\n");
  }
  printf("-------- availBoard -----------\n");

  for (size_t i = 0; i < BOARDBITS; i++) {
    cout << availBoard[i] << " ";
    if (((i + 1) % boardDim) == 0)
      printf("\n");
  }
  printf("----------------------------\n");
}

void KonaneBoard::getAvailMoves(char player) {
  // Purpose: Determin available moves for a player
  // Parameters:
  //   -player: char of player to find moves for
  // Post:
  //   -Clears availableMoves vector
  //   -Calls availableMovesX, availableMovesY,
  availableMoves.clear();
  for (int i = 0; i < BOARDBITS; i++) {
    if (checkEmpty(i)) {
      availableMovesX(i, player);
      availableMovesY(i, player);
    }
  }
  for (size_t i = 0; i < availableMoves.size(); i++) {
  }
}

void KonaneBoard::availableMovesX(int index, char player) {
  // Purpose: Append possible moves in the x direction for player at index
  // Parameters:
  //   -index: index of board
  //   -player: char of player to find moves for
  // Post: moves in x direction are appeneded to self.availableMoves

  int size = BOARDDIM;
  int xIndex =
      index % size; // Removes the y element of the index (0 <= xIndex <= 7)

  // Check right direction
  if (xIndex < size - 2) { // If not close to board right size
    if (checkPlayer(index + 1) != player &&
        !checkEmpty(index + 1)) { // if index+1 is opponent
      if (checkPlayer(index + 2) == player) {
        vector<int> moveVec = {index + 2, index};
        availableMoves.push_back(moveVec);
      }
    }
  }
  // Check Left Direction
  if (xIndex > 1) { // if index+1 is opponent
    if (checkPlayer(index - 1) != player &&
        !checkEmpty(index - 1)) { // Check if element beside is opponent
      if (checkPlayer(index - 2) == player) { // check if player
        vector<int> moveVec = {index - 2, index};
        availableMoves.push_back(moveVec);
      }
    }
  }
}

void KonaneBoard::availableMovesY(int index, char player) {
  // Purpose: Append possible moves in the y direction for player at index
  // Parameters:
  //   -index: index of board
  //   -player: char of player to find moves for
  // Post: moves in y direction are appeneded to self.availableMoves
  int size = BOARDDIM; // If BOARDDIM used directly in equations, strange
                       // behaviour occures
  int yIndex = index / size;
  // Check Down
  if (yIndex < size - 2) { // if not close to bottom
    if (checkPlayer(index + size) != player &&
        !checkEmpty(index + size)) { // Check if element beside is opponent
      if (checkPlayer(index + size * 2) == player) { // check if player
        vector<int> moveVec = {index + size * 2, index};
        availableMoves.push_back(moveVec);
      }
    }
  }
  // Check up
  if (yIndex > 1) { // if not close to top
    if (checkPlayer(index - size) != player &&
        !checkEmpty(index - size)) { // Check if element beside is opponent
      if (checkPlayer(index - size * 2) == player) { // check if player
        vector<int> moveVec = {index - size * 2, index};
        availableMoves.push_back(moveVec);
      }
    }
  }
}

bool KonaneBoard::checkEmpty(int index) {
  // checks the konaneBoard to see if the index is vacant
  // Returns: true if the index is empty, false otherwise

  return not availBoard[index];
}

char KonaneBoard::checkPlayer(int index) {
  // Purpose: Retrieves the char of the player at index
  // Parameters: index: Starting index of board to check
  // Pre: Index must be within bounds
  // Calls: CheckEmpty
  // Returns:
  //   -'O': (O as in Oscar) availBoard index is 0
  //   -'B': playerBoard index is 0
  //   -'W': playerBoard index is 1

  if (checkEmpty(index))
    return 'O'; // O as in Oscar
  int player = playerBoard[index];
  if (player)
    return 'W';
  else
    return 'B';
}

void KonaneBoard::movePlayer(int index, int index2, char player) {
  // Purpose: Move player from one index to another
  // Parameters:
  //   -index: Starting index which the player will move from
  //   -index2: Ending index which the player will move to
  //   -player: the char of the player to be moved
  //
  // Pre: Indices must be within bounds
  // Post:
  //   -availBoard: index and the middle index are set 0, index2 set to 1
  //   -playerBoard: index2 is set to player bit
  // Calls: removePlayer, placePlayer
  // Returns: void

  // remove start:
  removePlayer(index);
  // middle position is always average
  removePlayer((index + index2) / 2);
  placePlayer(index2, player);
}

void KonaneBoard::removePlayer(int index) {
  // Purpose: Remove player from a board index
  // Pre: Index must be within bounds
  // post: availBoard index is set to 0

  if (checkEmpty(index))
    throw invalid_argument("No player at index");
  availBoard ^= (Unit)1 << index;
}

void KonaneBoard::placePlayer(int index, char player) {
  // Purpose: Place player at index
  // Parameters:
  //  -index: index of board at which to place piece
  //  -player: the char of the player to be moved
  // Pre: Index must be within bounds
  // Post:
  //   -availBoard: index is set 1
  //   -playerBoard: index is set to player bit
  // Calls: CheckEmpty
  // Returns: void

  if (not checkEmpty(index))
    throw invalid_argument("Index not empty");
  availBoard ^= (Unit)1 << index; // flip available bit
  if (player == 'W')              // flip to 1
    playerBoard |= (Unit)1 << index;
  else
    playerBoard &= (~((Unit)1 << index)); // Setting indexed value to 0
}

void KonaneBoard::getUserInput(char player) {
  // Purpose: Prompt user for move and process move
  // Parameters:
  //  -player: the char of the user player to be placed
  // Post: availBoards & playerBoard: updated according to user input
  // Calls: removePlayer or movePlayer
  // Returns: void

  // Move will be in the form of E1
  string userIn;
  cout << player << ": ";
  cin >> userIn;

  // Conversion:
  //   -X changes letter to index starting at 0;
  //   -Y is inverted so [0] starts at top left

  // Single value edge case for first move
  if (userIn.size() == 2) {
    int xIndex1 = userIn[0] - 'A';
    int yIndex1 = 7 - (userIn[1] - '1'); // reduces to int and flips y value
    int combinedIndex1 = (yIndex1)*BOARDDIM + xIndex1;
    removePlayer(combinedIndex1);

  } else if (userIn.size() == 5 && userIn[2] == '-') {

    // Regular game move:
    int xIndex1 = userIn[0] - 'A';
    int yIndex1 = 7 - (userIn[1] - '1'); // reduces to int and flips y value
    int xIndex2 = userIn[3] - 'A';
    int yIndex2 = 7 - (userIn[4] - '1'); // reduces to int and flips y value

    // X and Y values are combined to make single index
    int combinedIndex1 = (yIndex1) * 8 + xIndex1;
    int combinedIndex2 = (yIndex2) * 8 + xIndex2;
    movePlayer(combinedIndex1, combinedIndex2, player);
  } else {
    cout << "INVALID INPUT: Format as A1-A3" << endl;
  }
}

vector<KonaneBoard> KonaneBoard::generateChildren() {
  // Purpose: Generate children nodes from the current state
  // Calls: -getAvailMoves()
  // Returns: children: Vector of KonaneBoard objects
  vector<KonaneBoard> children = {};
  getAvailMoves(playerChar);
  for (size_t i = 0; i < availableMoves.size(); i++) {
    KonaneBoard temp = KonaneBoard(availBoard, playerBoard, opponentChar);
    // Perform move on temp board
    temp.movePlayer(availableMoves[i][0], availableMoves[i][1], playerChar);
    children.push_back(temp);
  }
  return children;
}

int KonaneBoard::randomMove(char Player) {
  // Purpose: Make a random move for the specified player
  // Postconditions: Player makes a move on the board
  // Returns: 0 if move is successful, 1 otherwise

  // First Move Edgecase
  size_t count = 0;
  for (size_t i = 0; i < BOARDBITS; i++) {
    if (checkEmpty(i)) {
      count += 1;
    }
  }
  if (count < 2) {
    // play first move
    if (Player == 'B')
      removePlayer(36); // TODO: HardCoded
    else
      removePlayer(35);
  } else {

    // Get available moves and make random selection from vector
    getAvailMoves(Player);
    srand(time(NULL));
    if (availableMoves.size() == 0)
      return 1;
    int randomInt = rand() % availableMoves.size();

    movePlayer(availableMoves[randomInt][0], availableMoves[randomInt][1],
               Player);
  }
  return 0;
}
