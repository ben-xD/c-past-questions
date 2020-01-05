#include "playfair.h"

#include <string.h>
#include <cctype>

#include <iostream>

void prepare(const char* input, char* output) {
    char* output_initial = output;
    while(*input != '\0') {
        if (isalnum(*input)){
            *output = toupper(*input);
            output++;
        }
        input++;
    }

    if(strlen(output_initial) % 2 == 1) {
        *output = 'X';
        output++;
    }
    *output = '\0';
}

void grid(const char* codeword, char square[6][6]) {
    int row = 0;
    int col = 0;
    char used_characters[37];
    used_characters[0] = '\0';
    const char* codeword_ = codeword;
    while (*codeword != '\0') {
        if (strchr(used_characters, *codeword) == NULL) {
            square[row][col] = *codeword;
            col++;
            if (col > 5) {
                col = 0;
                row++;
            }
            strncat(used_characters, codeword, 1);
        }
        codeword++;
    }
    codeword = codeword_;

    for (int i = 'A'; i <= 'Z'; i++) {
        if (strchr(used_characters, i) == NULL) {
            square[row][col] = i;
            col++;
            if (col > 5) {
                col = 0;
                row++;
            }
        }
    }

    for (int i = '0'; i <= '9'; i++) {
        if (strchr(used_characters, i) == NULL) {
            square[row][col] = i;
            col++;
            if (col > 5) {
                col = 0;
                row++;
            }
        }
    }
}

int find_row_of(char square[6][6], char ch) {
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 6; col++) {
            if (square[row][col] == ch) {
                return row;
            }
        }
    }
}

int find_col_of(char square[6][6], char ch) {
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 6; col++) {
            if (square[row][col] == ch) {
                return col;
            }
        }
    }
    return -1;
}

void bigram(char square[6][6], char in1, char in2, char& out1, char& out2) {
    int in1_row = find_row_of(square, in1);
    int in1_col = find_col_of(square, in1);
    int in2_row = find_row_of(square, in2);
    int in2_col = find_col_of(square, in2);
    out1 = square[in1_row][in2_col];
    out2 = square[in2_row][in1_col];
}

void encode(char square[6][6], const char* prepared, char* encoded) {
    std::cout << prepared << std::endl;
    if (*prepared == '\0') {
        return;
    }

    bigram(square, prepared[0], prepared[1], encoded[0], encoded[1]);
    encoded[2] = '\0';
    encode(square, prepared+2, encoded+2);
    return;
}