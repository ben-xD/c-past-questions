#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

#include <iostream>

using namespace std;

#include "tube.h"

void set_station_from_symbol(char symbol, char* destination);


/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
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

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}

// TODO switch to const refs, for efficiency? check perf
bool get_symbol_position(char** map, int height, int width, char target, int& row, int& column) {
  for (row = 0; row < height; row++) {
    for (column = 0; column < width; column++) {
      if (map[row][column] == target) {
        return true;
      }
    }
  }
  return false;
}

bool get_symbol_for_station(const char* name, char& symbol_return) {
  std::ifstream file;
  file.open("stations.txt");
  char station_name[512];
  char symbol;
  while(file.good()) {
    file >> symbol;
    file.ignore(1);
    file.getline(station_name, 512);
    if (!strcmp(station_name, name)) {
      symbol_return = symbol;
      file.close();
      return true;
    }
  }
  file.close();
  return false;
}

bool get_symbol_for_line(const char* name, char& symbol_return) {
  std::ifstream file;
  file.open("lines.txt");
  char line_name[512];
  char symbol;
  while(file.good()) {
    file >> symbol;
    file.ignore(1);
    file.getline(line_name, 512);
    if (!strcmp(name, line_name)) {
      symbol_return = symbol;
      file.close();
      return true;
    }
  }
  file.close();
  return false;
}

char get_symbol_for_station_or_line(const char* name) {
  char symbol = '_';
  get_symbol_for_station(name, symbol);
  get_symbol_for_line(name, symbol);
  return symbol;
}

// returns #line changes
int validate_route(char** map, int height, int width, const char* start_station, const char* route, char* destination) {
  // validate start station: get symbol, check if station
  char symbol;
  if (!get_symbol_for_station(start_station, symbol)) {
    return ERROR_START_STATION_INVALID;
  }
  
  int row, column;
  get_symbol_position(map, height, width, symbol, row, column);

  int line_changes = -1;
  char current_line;

  while (strlen(route)) {
    if (*route == '\0') {
      return line_changes;
    }
    if (!isalnum(*route)) {
      route++;
    }

    char string_direction[3];
    if (isalpha(route[0])) {
      if (isalpha(route[1])) {
        strncpy(string_direction, route, 2);
        string_direction[2] = '\0';
        route+=2;
      } else {
        strncpy(string_direction, route, 1);
        string_direction[1] = '\0';
        route+=1;
      }
    }

    Direction direction = string_to_direction(string_direction);
    if (direction == INVALID_DIRECTION) {
      return ERROR_INVALID_DIRECTION;
    }

    // Move piece in direction.
    int next_row = row;
    int next_col = column;
    if (direction == N || direction == NW || direction == NE) {
      next_row--;
    }
    if (direction == S || direction == SW || direction == SE) {
      next_row++;
    }
    if (direction == W || direction == SW || direction == NW) {
      next_col--;
    }
    if (direction == E || direction == SE || direction == NE) {
      next_col++;
    }

    if (next_row >= height || next_row < 0 || next_col >= width || next_col < 0) {
      return ERROR_OUT_OF_BOUNDS;
    }
    if (map[next_row][next_col] == ' ') {
     return ERROR_OFF_TRACK;
    }

    std::cout << next_row << ", next col: " << next_col << std::endl;

    // cannot directly change from line to line. need to go through station
    if (!isalnum(map[row][column]) && !isalnum(map[next_row][next_col]) && map[row][column] != map[next_row][next_col]) {
      return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
    }
    if (!isalnum(map[row][column])) {
      if (current_line != map[row][column]) {
        line_changes++;
      }
      current_line = map[row][column];
    }

    // or use a stack?/ recursion?
    // or check for 'opposite' moves (don't allow W if E)
    // store visited locations since station
    // if (isalnum(map[next_row][next_col])) {
    //   // clear stored track if station
    // } else if (next_row, next_col already in stored track) {
    //   return ERROR_BACKTRACKING_BETWEEN_STATIONS;
    // }

    // move
    row = next_row;
    column = next_col;
  }

  // check destination. If station, return
  if (!isalnum(map[row][column])) {
    return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;
  }
  // Set destination to be station.
  set_station_from_symbol(symbol, destination);
  
  return line_changes;
}

void set_station_from_symbol(char symbol, char* destination) {
    // get station name for symbol from file.
  std::ifstream file;
  file.open("stations.txt");

  char symbolInput;
  char name[512];
  
  while (file.good()) {
    file >> symbolInput;
    file.ignore(1);
    file >> name;
    if (symbolInput == symbol) {
      strcpy(destination, name);
      break;
    } 
  }
}