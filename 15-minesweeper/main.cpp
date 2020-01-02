#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "minesweeper.h"

using namespace std;

void print_move_result(MoveResult result, char revealed[9][9]) {
  switch (result) {
  case INVALID_MOVE:
    cout << "Invalid move." << endl;
    return;
  case REDUNDANT_MOVE:
    cout << "Square is already uncovered or flagged." << endl;
    return;
  case BLOWN_UP:
    cout << "You uncovered a mine and have been blown up!" << endl;
    return;
  case SOLVED_BOARD:
    cout << "You have solved the board, well done!" << endl;
    break;
  case VALID_MOVE:
    cout << "Valid move." << endl;
    break;
  }
  display_board(revealed);
}

int main() {

  char mines[9][9], revealed[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("mines.dat", mines);

  cout << endl << "Displaying mine positions with display_board():" << endl;
  display_board(mines);
  cout << "Done!" << endl << endl;

  cout << "Calling initialise_board()..." << endl;
  initialise_board(revealed);

  cout << endl << "Displaying initial playing board with display_board():" << endl;
  display_board(revealed);
  cout << "Done!" << endl << endl;

  cout << "====================== Question 1 ======================" << endl << endl;

  load_board("partial.dat", revealed);
  display_board(revealed);
  cout << "Game is ";
  if (!is_complete(mines, revealed))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("solution.dat", revealed);
  display_board(revealed);
  cout << "Game is ";
  if (!is_complete(mines, revealed))
    cout << "NOT ";
  cout << "complete." << endl;
  
  cout << "====================== Question 2 ======================" << endl << endl;

  load_board("mines.dat", mines);

  cout << "Found " << count_mines("A7", mines) << " mine(s) around square 'A7'" << endl;
  
  cout << "Found " << count_mines("E5", mines) << " mine(s) around square 'E5'" << endl;

  cout << "Found " << count_mines("H9", mines) << " mine(s) around square 'H9'" << endl << endl;

  cout << "====================== Question 3 ======================" << endl << endl;

  load_board("mines.dat", mines);
  initialise_board(revealed);
  display_board(revealed);
  
  /* valid move */
  cout << "Making move 'B6' results in:" << endl;
  MoveResult result = make_move("B6", mines, revealed);
  print_move_result(result, revealed);

  /* valid move */
  cout << "Making move 'E5' results in:" << endl;
  result = make_move("E5", mines, revealed);
  print_move_result(result, revealed);
  
  /* valid move */
  cout << "Making move 'H3*' results in:" << endl;
  result = make_move("H3*", mines, revealed);
  print_move_result(result, revealed);

  /* invalid move */
  cout << "Making move 'Z8' results in:" << endl;
  result = make_move("Z8", mines, revealed);
  print_move_result(result, revealed);

  /* blown up */
  cout << "Making move 'A5' results in:" << endl;
  result = make_move("A5", mines, revealed);
  print_move_result(result, revealed);

  cout << "====================== Question 4 ======================" << endl << endl;

  load_board("mines.dat", mines);
  load_board("partial.dat", revealed);
  display_board(revealed);
  
  cout << "Safe move sequence: " << endl;
  char move[512];
  while (find_safe_move(revealed, move)) {
    cout << move << " ";
    make_move(move, mines, revealed);
  }
  cout << endl;

  /*  
  cout << "=================== Bonus Question =====================" << endl << endl;

  load_board("bonus.dat", mines);
  initialise_board(revealed);

  char moves[512];
  solve_board(mines, revealed, moves);

  cout << "The set of risky moves required to solve the bonus board is:" << endl;
  cout << moves << endl;
  */
  return 0;
}
