#include "piglatin.h"
#include <iostream>
#include <cctype>
#include <cstring>

const char* WAY = "way";
const char* AY = "ay";

int findFirstVowel(const char* word) {
    for (size_t i = 0; i < strlen(word); i++) {
        if (isVowel(word[i], i, strlen(word))) {
            return i;
        }
    }
    return -1;
}

// by default
bool isVowel(char character, int position, int length) {
    bool isEnd = position == length - 1 || position == 0;
    
    char lowercasedChar = tolower(character);
    switch(lowercasedChar) {
        case 'a': 
        case 'e': 
        case 'i': 
        case 'o': 
        case 'u': 
            return true;
        case 'y': 
            if (!isEnd) {
                return true;
            } else {
                return false;
            }
        default:
            return false;
    }
}

void translateWord(const char* english, char* piglatin) {  
    bool isCapitalised = isupper(english[0]);
    char* uncapitalisedEnglish = new char[strlen(english)];
    strcpy(uncapitalisedEnglish, english);
    if (isCapitalised) {
        uncapitalisedEnglish[0] = tolower(uncapitalisedEnglish[0]);
    }
    
    if (isVowel(uncapitalisedEnglish[0], 0, strlen(uncapitalisedEnglish))) {
        // add 'way'
        strcpy(piglatin, uncapitalisedEnglish);
        strcpy(piglatin + strlen(uncapitalisedEnglish), WAY);
    } else if (isdigit(uncapitalisedEnglish[0])) {
        strcpy(piglatin, uncapitalisedEnglish);
    } else {
        int firstVowel = findFirstVowel(uncapitalisedEnglish);
        if (firstVowel == -1) {
            strcpy(piglatin, uncapitalisedEnglish);
            strcpy(piglatin + strlen(uncapitalisedEnglish), AY);
        } else {
            // move all chars before vowel
            strcpy(piglatin, uncapitalisedEnglish + firstVowel);
            strncpy(piglatin + strlen(piglatin), uncapitalisedEnglish, firstVowel);
            // add ay
            strcpy(piglatin + strlen(uncapitalisedEnglish), AY);
        }
    }

    if (isCapitalised && strlen(piglatin) > 0) {
        piglatin[0] = toupper(piglatin[0]);
    }

    delete [] uncapitalisedEnglish;
}

void translateStream(std::istream& input, std::ostream& output) {
    char english[64];
    char piglatin[67];

    int i = 0;
    while (isalnum(input.peek())) {
        *(english+i) = input.get();
        i++;
    }
    english[i] = '\0';

    translateWord(english, piglatin);
    output << piglatin;

    while(!isalnum(input.peek())) {
        if (!input.good()) {
            return;
        }
        output << (char) input.get();
    }

    translateStream(input, output);
}