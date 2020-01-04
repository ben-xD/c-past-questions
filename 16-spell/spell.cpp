#include <iostream>
#include "spell.h"
#include <string.h>

using namespace std;

int frequency(const char* target) {
    std::ifstream file;
    file.open("words.dat");
    int count = 0;
    char word[MAX_LENGTH];
    while(file.good()) {
        file >> count; 
        file >> word;
        int cmp = strcmp(word, target);
        if (!cmp) {
            break;
        }
        count = 0;
    }
    file.close();
    return count;
}

int edit_distance_bonus(const char* a, const char* b, int max_d) {
    return edit_distance(a, b, max_d);
}


int edit_distance(const char* a, const char* b, int max_d) {
    int a_len = strlen(a);
    int b_len = strlen(b);

    if (max_d < 0) {
        return max(a_len, b_len);
    }

    if (min(a_len, b_len) == 0) {
        return max(a_len, b_len);
    }

    int indicator = *a != *b;
    if (a_len > 1 && b_len > 1 && *a == *(b+1) && *b == *(a+1)) {
        // recursive calls
        int one = edit_distance(a+1, b, max_d-1) + 1;
        int two = edit_distance(a, b+1, max_d-1) + 1;
        int three = edit_distance(a+1, b+1,max_d) + indicator;
        int four = edit_distance(a+2, b+2,max_d-1) + 1;
        return min(min(one,two), min(three,four));
    }

    int one = edit_distance(a+1, b,max_d-1) + 1;
    int two = edit_distance(a, b+1,max_d-1) + 1;
    int three = edit_distance(a+1, b+1,max_d) + indicator;
    return min(one, min(two, three));
}

bool spell_correct(const char* word, char* output) {
    strcpy(output, word);
    std::ifstream file;
    file.open("words.dat");

    int best_distance = 99;
    int max_count = 0;

    char input[MAX_LENGTH];
    while (file.good()) {
        int count = 0;
        file >> count >> input;
        
        if (!strcmp(input, word)) {
            strcpy(output, word);
            file.close();
            return false;
        }

        int distance = edit_distance(input, word, 2);
        if (distance <= 2 && distance < best_distance) {
            strcpy(output, input);
            max_count = count;
            best_distance = distance;
        } else if (distance <= 2 && distance == best_distance && count > max_count) {
            strcpy(output, input);
            max_count = count;
        }
    }
    file.close();

    if (strcmp(output, word)) {
        return true;
    }

    return false;
}