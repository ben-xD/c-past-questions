#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "minesweeper.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load mine positions from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || buffer[n] == '*' || buffer[n] == ' ' || buffer[n] == '?' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << "|";
  for (int i=0; i<9; i++) 
    cout << ( (data[i]=='.') ? ' ' : data[i]);
  cout << "|" << endl;
}

/* pre-supplied function to display a minesweeper board */
void display_board(const char board[9][9]) {
  cout << "  ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r);
  cout <<  endl;
  cout << " +---------+" << endl;
  for (int r=0; r<9; r++) 
    print_row(board[r],r);
  cout << " +---------+" << endl;
}

/* pre-supplied function to initialise playing board */ 
void initialise_board(char board[9][9]) {
  for (int r=0; r<9; r++)
    for (int c=0; c<9; c++)
      board[r][c] = '?';
}

bool is_complete(const char board[9][9], const char revealed[9][9]){
  // if '.' in board and '?' in revealed, return false
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (board[row][col] == '.' && revealed[row][col] == '?') {
        return false;
      }
    }
  }
  return true;
}

int count_mines(const char* position, const char board[9][9]) {
  int row = position[0] - 'A';
  int col = position[1] - '1';
  return count_mines(row, col, board);
}

int count_mines(int pos_row, int pos_col, const char board[9][9], char character) {
  int count = 0;
  for (int row = pos_row - 1; row <= pos_row + 1; row++) {
    for (int col = pos_col - 1; col <= pos_col + 1; col++) {
      if (in_boundary(row, col) && board[row][col] == character) {
        count++;
      }
    }
  }
  return count;
}

MoveResult make_move(const char* position, const char mines[9][9], char revealed[9][9]) {
  if (strlen(position) > 2 && position[2] != '*') {
    return INVALID_MOVE;
  }

  int row = position[0] - 'A';
  int col = position[1] - '1';
  if (!in_boundary(row, col)) {
    return INVALID_MOVE;
  }

  if (revealed[row][col] != '?') {
    return REDUNDANT_MOVE;
  }

  if (strlen(position) == 3) {
    revealed[row][col] = '*';
    return VALID_MOVE;
  }

  if (mines[row][col] == '*') {
    return BLOWN_UP;
  }

  make_move(row, col, mines, revealed);
  if (is_complete(mines, revealed)) {
    return SOLVED_BOARD;
  }
  return VALID_MOVE;
}

void make_move(int row, int col, const char mines[9][9], char revealed[9][9]) {
  if (mines[row][col] == '*') {
    return; // do nothing if mine
  }

  int mine_count = count_mines(row, col, mines);

  // if mines > 0, display in revealed
  if (mine_count != 0) {
    revealed[row][col] = mine_count + '0';
    return;
  }

  revealed[row][col] = ' ';
  // if 0, recursively call surrounding squares
  for (int row_ = row - 1; row_ <= row + 1; row_++) {
    for (int col_ = col - 1; col_ <= col + 1; col_++) {
      if (in_boundary(row_, col_) && revealed[row_][col_] == '?') {
        make_move(row_, col_, mines, revealed);
      }
    }
  }
  return;
}

bool in_boundary(int row, int col) {
  return row >= 0 && row < 9 && col >= 0 && col < 9;
}

// uncover OR flag move safely
bool find_safe_move(char revealed[9][9], char* move) {
  // iterate over each cell:
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (!(revealed[row][col] >= '1' && revealed[row][col] < '9')) {
        continue; // only work with numbers
      }
      int mine_count = count_mines(row, col, revealed);
      int unknown_count = count_mines(row, col, revealed, '?');
      int revealed_count = revealed[row][col] - '0';

      // If all  == unknowns count. Flag 1 of them, return
      if (revealed_count - mine_count == unknown_count) {
        // find one ?, and set flag.
        for (int r = row-1; r <= row+1; r++) {
          for (int c = col-1; c <= col+1; c++) {
            if (in_boundary(r,c) && revealed[r][c] == '?') {
              move[0] = r + 'A';
              move[1] = c + '1';
              move[2] = '*';
              move[3] = '\0';
              return true;
            }
          }
        }
      }

      // if #displayed == #mines visible, then reveal any surrounding question mark, return
      if (revealed_count == mine_count) {
        // find one question mark, and set move to it (without *)
        for (int r = row-1; r <= row+1; r++) {
          for (int c = col-1; c <= col+1; c++) {
            if (in_boundary(r,c) && revealed[r][c] == '?') {
              move[0] = r + 'A';
              move[1] = c + '1';
              move[2] = '\0';
              return true;
            }
          }
        }
      }
      
      // add more rules?
    }
  }
  
  // nothing found
  strcpy(move, "");
  return false;
}