#include <iostream>
#include <fstream>

/* you may assume a maximum word length of 512 characters*/
#define MAX_LENGTH 512

/* insert your function prototypes here */
int frequency(const char* target);
// int edit_distance(const char* a, const char* b);
int edit_distance(const char* a, const char* b, int max_d = 99);
int edit_distance_bonus(const char* a, const char* b, int max_d = 99);
bool spell_correct(const char* word, char* output);
