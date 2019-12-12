/* you may assume a maximum word length of 512 characters*/
#define MAX_LENGTH 512

#include <limits.h>

int frequency(const char* target);
bool spell_correct(const char *word, char *fixed);
int edit_distance(const char *from, const char *to, int max = INT_MAX);