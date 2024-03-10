#include "KonaneBoard.hpp"
#include <iostream>

bool testKonaneBoardConstructor() {
  bool flag = true;
  KonaneBoard board = KonaneBoard('B');
  if (board.availBoard != 0xFFFFFFFFFFFFFFFF)
    cout << "testKonaneBoardConstructor availBoard: " << flag << endl;
  if (board.playerBoard != 0x55aa55aa55aa55aa)
    cout << "testKonaneBoardConstructor playerBoard: " << flag << endl;
  return flag;
}

bool testCheckPlayer() {
  bool flag = true;
  KonaneBoard board = KonaneBoard('B');
  board.playerBoard[0] = 0;
  if (board.checkPlayer(0) != 'B') {
    cout << "Check Black Player: Fail" << endl;
    flag = false;
  }
  board.playerBoard[0] = 1;
  if (board.checkPlayer(0) != 'W') {
    cout << "Check White Player: Fail" << endl;
    flag = false;
  }
  board.availBoard[0] = 0;
  if (board.checkPlayer(0) != 'O') {
    cout << "Check for Empty space in CheckPlayer: Fail" << endl;
    flag = false;
  }
  return flag;
}

/*
bool testPrintBoard() {

  bool flag = true;
  KonaneBoard board = KonaneBoard('B');

  // first print output to text file
  ofstream outputFile("output.txt");
  streambuf *coutBuffer = cout.rdbuf(); // Save current output buffer
  cout.rdbuf(outputFile.rdbuf());       // redirect buffer to output.txt

  if (!outputFile.is_open()) {
    cerr << "ERROR: Unable to open file for writing" << endl;
    return 0;
  }
  board.printBoard(); // will print board to output.txt
  outputFile.close();
  cout.rdbuf(coutBuffer); // restore original buffer

  // Check if output.txt and testPrintBoard.txt are equal
  ifstream printBoardText;
  ifstream testPrintBoardText;
  printBoardText.open("output.txt");
  testPrintBoardText.open("./testing/testPrintBoardText.txt");

  // Ensure files opened
  if (!printBoardText.is_open()) {
    cerr << "ERROR: Unable to open outputFile.txt for reading" << endl;
    return 0;
  }
  if (!testPrintBoardText.is_open()) {
    cerr << "ERROR: Unable to open testPrintBoardText file for reading" << endl;
    return 0;
  }
  // Loop through each line and compare strings
  string line1, line2;
  while (getline(printBoardText, line1) && getline(testPrintBoardText, line2)) {
    if (line1 != line2) {
      cout << "testPrintBoard equal lines: Fail!" << endl;
      flag = false;
    }
  }
  // checks if reached EOF:
  if (!(printBoardText.eof() && testPrintBoardText.eof())) {
    cout << "testPrintBoard: reached end of file at same time: Fail!" << endl;
    flag = false;
  }

  testPrintBoardText.close();
  printBoardText.close();

  if (std::remove("outputFile.txt") != 0) { // Remove printed file
    std::cerr << "Error: Unable to delete file!" << std::endl;
  }

  return flag;
}


bool testPrintBoardBits() {
  bool flag = true;
  KonaneBoard board = KonaneBoard('B');

  return flag;
}
*/

bool testCheckEmpty() {
  bool flag = true;
  KonaneBoard board = KonaneBoard('B');
  board.availBoard[BOARDBITS - 1] = 0; // make index empty
  if (board.checkEmpty(BOARDBITS - 1) != 1) {
    cout << "Check for Empty space at end of file: Fail" << endl;
    flag = false;
  }
  board.availBoard[BOARDBITS - 1] = 1;
  if (board.checkEmpty(BOARDBITS - 1) != 0) {
    cout << "Check square is not empty at end of file: Fail" << endl;
    flag = false;
  }
  board.availBoard[0] = 0; // make index empty
  if (board.checkEmpty(0) != 1) {
    cout << "Check for Empty space at start of file: Fail" << endl;
    flag = false;
  }
  board.availBoard[0] = 1;
  if (board.checkEmpty(0) != 0) {
    cout << "Check square is not empty at start of file: Fail" << endl;
    flag = false;
  }

  return flag;
}

bool testMovePlayer() {
  // have not set up error check for false moves
  // SETUP
  bool flag = true;
  KonaneBoard board = KonaneBoard('B');
  board.availBoard[10] = 1;
  board.availBoard[11] = 1;
  board.availBoard[12] = 0;
  board.playerBoard[10] = 0;

  board.movePlayer(10, 12, 'B');

  // ASSERT
  if (board.availBoard[10] != 0) {
    cout
        << "testMovePlayer: Black: Did not remove player from start index: Fail"
        << endl;
    flag = false;
  }
  if (board.availBoard[11] != 0) {
    cout << "testMovePlayer: Black: Did not remove jumped player from middle "
            "index: Fail"
         << endl;
    flag = false;
  }
  if (board.availBoard[12] != 1) {
    cout << "testMovePlayer: Black: Did not place player at end index "
            "(availBoard): Fail"
         << endl;
    flag = false;
  }
  if (board.playerBoard[12] != 0) {
    cout << "testMovePlayer: Black: Did not place player at end index "
            "(playerBoard): Fail"
         << endl;
    flag = false;
  }
  // SETUP
  board.availBoard[10] = 1;
  board.availBoard[11] = 1;
  board.availBoard[12] = 0;
  board.playerBoard[10] = 1;
  board.playerBoard[10] = 0;
  board.movePlayer(10, 12, 'W');

  // ASSERT
  if (board.availBoard[10] != 0) {
    cout
        << "testMovePlayer: White: Did not remove player from start index: Fail"
        << endl;
    flag = false;
  }
  if (board.availBoard[11] != 0) {
    cout << "testMovePlayer: White: Did not remove jumped player from middle "
            "index: Fail"
         << endl;
    flag = false;
  }
  if (board.availBoard[12] != 1) {
    cout << "testMovePlayer: White: Did not place player at end index "
            "(availBoard): Fail"
         << endl;
    flag = false;
  }
  if (board.playerBoard[12] != 1) {
    cout << "testMovePlayer: White: Did not place player at end index "
            "(playerBoard): Fail"
         << endl;
    flag = false;
  }

  return flag;
}

bool testRemovePlayer() {
  bool flag = true;
  KonaneBoard board = KonaneBoard('B');
  board.availBoard[0] = 1;
  board.removePlayer(0);
  if (board.availBoard[0] != 0) {
    cout << "testRemovePlayer: Did not remove player from board: Fail" << endl;
    flag = false;
  }

  board.availBoard[0] = 0;
  try {
    board.removePlayer(0);
    cout << "testRemovePlaye: Tried to remove player at already empty space: "
            "Fail"
         << endl;
    flag = false;
  } catch (const std::exception &) {
  }

  return flag;
}

bool testPlacePlayer() {
  bool flag = true;
  KonaneBoard board = KonaneBoard('B');

  // Black test
  board.availBoard[0] = 0;
  board.playerBoard[0] = 1;
  board.placePlayer(0, 'B');
  if (board.availBoard[0] != 1) {
    cout << "testPlacePlayer: Did not place on availBoard: Fail" << endl;
    flag = false;
  }
  if (board.playerBoard[0] != 0) {
    cout << "testPlacePlayer: Did not place black player on playerBoard: Fail"
         << endl;
    flag = false;
  }
  // White test
  board.availBoard[0] = 0;
  board.playerBoard[0] = 0;
  board.placePlayer(0, 'W');
  if (board.availBoard[0] != 1) {
    cout << "testPlacePlayer: Did not place on availBoard: Fail" << endl;
    flag = false;
  }
  if (board.playerBoard[0] != 1) {
    cout << "testPlacePlayer: Did not place White player on playerBoard: Fail"
         << endl;
    flag = false;
  }

  return flag;
}

int main() {
  // this is where all tests are run from
  cout << "-------- START TESTING KonaneBoard --------------" << endl;
  bool flag = true;
  flag &= testKonaneBoardConstructor(); // Constructor
  flag &= testCheckPlayer();
  // flag && testPrintBoard();
  // testPrintBoardBits();
  flag &= testCheckEmpty();
  flag &= testMovePlayer();
  flag &= testRemovePlayer();
  flag &= testPlacePlayer();
  if (flag)
    cout << "All tests Passed!!!" << endl;
  cout << "-------- DONE TESTING KonaneBoard --------------" << endl;
  return 0;
}
