#include "spell.h"

#include <fstream>
#include <iostream>
#include <limits.h>

int frequency(const char* target) {
    std::ifstream f;
    f.open("words.dat");
    int count;
    char word[MAX_LENGTH];
    while (f.good()) {
        f >> count >> word;
        if (strcmp(word, target) == 0) {
            return count;
        }
    }
    return 0;
}

int edit_distance(const char *from, const char *to, int max) {

    int from_s = strlen(from);
    int to_s = strlen(to);
    if (max < 0 || std::min(from_s, to_s) == 0) {
        return std::max(from_s, to_s);
    }

    int indicator_value = (from[0] == to[0]) ? 0 : 1;

    if (from_s >= 2 && to_s >= 2) {
        if (from[0] == to[1] && from[0] == to[1]) {
            int a = edit_distance(from+1, to, max - 1) + 1;
            int b = edit_distance(from, to+1, max - 1) + 1;
            int c = edit_distance(from+1, to+1, max) + indicator_value;
            int d = edit_distance(from + 2, to + 2, max - 1) + 1;
            return std::min(std::min(a, b), std::min(c, d));
        }
    }

    int a = edit_distance(from + 1, to, max - 1) + 1;
    int b = edit_distance(from, to+1, max - 1) + 1;
    int c = edit_distance(from+1, to+1, max) + indicator_value;
    return std::min(a, std::min(b, c));
}

bool spell_correct(const char* word, char* fixed) {
    strcpy(fixed, word);
    std::ifstream f;
    f.open("words.dat");
    
    int best_d = INT_MAX; 
    int best_count = 0;
    
    char current_word[MAX_LENGTH];
    int current_count;

    while (f.good())
    {
        f >> current_count >> current_word;
        int d = edit_distance(word, current_word, 2);
        if (d <= 2 && d < best_d)
        {
            strcpy(fixed, current_word);
            best_count = current_count;
            best_d = d;
        }
        else if (d <= 2 && d == best_d && current_count > best_count)
        {
            strcpy(fixed, current_word);
            best_count = current_count;
        }
    }
    f.close();

    if (strcmp(fixed, word) != 0) {
        return true;
    }

    return false;
}