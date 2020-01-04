#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

using namespace std;

#include "river.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new (nothrow) char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new (nothrow) char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* pre-supplied function which creates an empty ASCII-art scene */
char **create_scene() {
  char **scene = allocate_2D_array(SCENE_HEIGHT, SCENE_WIDTH);

  for (int i=0; i<SCENE_HEIGHT; i++) 
    for (int j=0; j<SCENE_WIDTH; j++)
      scene[i][j] = ' ';

  return scene;
}

/* pre-supplied function which frees up memory allocated for an ASCII-art scene */
void destroy_scene(char **scene) {
  deallocate_2D_array(scene, SCENE_HEIGHT);
}

/* pre-supplied function which displays an ASCII-art scene */
void print_scene(char **scene) {
  for (int i=0; i<SCENE_HEIGHT; i++) {
    for (int j=0; j<SCENE_WIDTH; j++)
      cout << scene[i][j];
    cout << endl;
  }
}

/* helper function which removes carriage returns and newlines from strings */
void filter(char *line) {
  while (*line) {
    if (*line >= ' ')
      line++;
    else 
      *line = '\0';
  }
}

/* pre-supplied function which inserts an ASCII-art drawing stored in a file
   into a given ASCII-art scene starting at coordinates (row,col)  */
bool add_to_scene(char **scene, int row, int col, const char *filename) {

  ifstream in(filename);
  if (!in)
    return false;

  int start_col = col;
  char line[512];
  in.getline(line,512);
  filter(line);
  while (!in.fail()) {
    for (int n=0; n<strlen(line); n++) {
      if (row >= SCENE_HEIGHT)
	return false;
      if (col >= SCENE_WIDTH)
	break;
      scene[row][col++] = line[n];
    }
    row++;
    col = start_col;
    in.getline(line,512);
    filter(line);
  }
  return true;
}

/* pre-supplied helper function to report the status codes encountered in Question 3 */
const char *status_description(int code) {
  switch(code) {
  case ERROR_INVALID_CANNIBAL_COUNT:
    return "Invalid cannibal count";
  case ERROR_INVALID_MISSIONARY_COUNT:
    return "Invalid missionary count";
  case ERROR_INVALID_MOVE:
    return "Invalid move";
  case ERROR_MISSIONARIES_EATEN:
    return "The missionaries have been eaten! Oh dear!";
  case ERROR_INPUT_STREAM_ERROR:
    return "Unexpected input stream error";
  case ERROR_BONUS_NO_SOLUTION:
    return "No solution";
  case VALID_GOAL_STATE:
    return "Problem solved!";
  case VALID_NONGOAL_STATE:
    return "Valid state, everything is OK!";
  }
  return "Unknown error";
}

void draw_boat(char** scene, bool left) {
  if (left) {
    add_to_scene(scene, 17, 19, "boat.txt");
  } else {
    add_to_scene(scene, 17, 36, "boat.txt");
  }
}

// bool add_to_scene(char **scene, int row, int col, const char *filename) 

/* insert your functions here */
char** make_river_scene(const char* left, const char* boat) {
  char** scene = create_scene();
  add_to_scene(scene, 0, 0, "bank.txt");
  add_to_scene(scene, 0, 53, "bank.txt");
  add_to_scene(scene, 3, 30, "sun.txt");
  add_to_scene(scene, 19, 19, "river.txt");

  // count M, C. check for B
  int left_c = 0;
  int left_m = 0;
  bool left_boat = false;
  while (*left != '\0') {
    switch(*left) {
      case 'M':
        left_m++;
        break;
      case 'C':
        left_c++;
        break;
      case 'B':
        left_boat = true;
        break;
    }
    left++;
  }

  for (int i = 0; i < left_m; i++) {
    add_to_scene(scene, 2, 1+i*6, "missionary.txt");
  }
  for (int i = 0; i < left_c; i++) {
    add_to_scene(scene, 11, 1+i*6, "cannibal.txt");
  }

  int boat_m = 0;
  int boat_c = 0;

  // boat: 0-2 chars: M & C
  while (*boat != '\0') {
    switch(*boat) {
      case 'M':
        boat_m++;
        break;
      case 'C':
        boat_c++;
        break;
    }
    boat++;
  }
    //  draw boat
  draw_boat(scene, left_boat);
  int available_seat;
  if (left_boat) {
    available_seat = 22;
  } else {
    available_seat = 39;
  }
  for (int i = 0; i < boat_c; i++) {
    add_to_scene(scene, 11, available_seat, "cannibal.txt");
    available_seat += 6;
  }
  for (int i = 0; i < boat_m; i++) {
    add_to_scene(scene, 11, available_seat, "missionary.txt");
    available_seat += 6;
  }

  for (int i = 0; i < 3-left_m-boat_m; i++) {
    add_to_scene(scene, 2, 54+i*6, "missionary.txt");
  }
  for (int i = 0; i < 3-left_c-boat_c; i++) {
    add_to_scene(scene, 11, 54+i*6, "cannibal.txt");
  }
  // draw right bank?

  return scene;
}

int perform_crossing(char* left, const char* targets) {
  if (strlen(targets) < 1 && strlen(targets) > 2) {
    return ERROR_INVALID_MOVE;
  }

  std::cout << "Loading the boat..." << left << std::endl;
  int m_count = count_char(left, 'M');
  int c_count = count_char(left, 'C');
  int m_boat_count = count_char(targets, 'M');
  int c_boat_count = count_char(targets, 'C');
  
  *left = '\0';
  // move from left bank to boat
  for (int i = 0; i < m_count - m_boat_count; i++) {
    strcat(left, "M");
  }
  for (int i = 0; i < c_count - c_boat_count; i++) {
    strcat(left, "C");
  }
  strcat(left, "B"); // boat on left
  char** scene = make_river_scene(left, targets);
  print_scene(scene);

  // cross river
  left[strlen(left)-1] = '\0'; // boat on right
  std::cout << "Crossing the river..." << std::endl;
  scene = make_river_scene(left, targets);
  print_scene(scene);

  // unload boat
  std::cout << "Unloading the boat..." << std::endl;
  scene = make_river_scene(left, "");
  print_scene(scene);

  int right_c_count = 3 + c_boat_count - count_char(left, 'C');
  int right_m_count = 3 - m_count;
  if (right_m_count && right_m_count < right_c_count) {
    return ERROR_MISSIONARIES_EATEN;
  }

  m_count = count_char(left, 'M');
  if (right_m_count != 3) {
    return VALID_NONGOAL_STATE;
  }

  return VALID_GOAL_STATE;

}

int count_char(const char* word, char character) {
  int count = 0;
  while (*word != '\0') {
    if (*word == character) {
      count++;
    };
    word++;
  }
  return count;
}

int play_game() {
  char left[7] = "";
  std::cout << "Enter initial state of left bank: ";
  std::cin >> left;
  char target[10] = "";
  std::cout << "Enter boat configuration: ";
  std::cin >> target;
  return perform_crossing(left, target);
}