#include <cctype>
#include <iostream>

char encode(const char character) {
    char words[26] = {'0','1','2','3','0','1','2','0','0','2','2','4','5','5','0','1','2','6','2','3','0','1','0','2','0','2'};
    return words[toupper(character) - 65];
}

void encode(const char* surname, char soundex[5]) {
    int soundex_pos = 0;
    soundex[soundex_pos++] = toupper(*surname);

    char previous_character = 0;

    while(soundex_pos < 4 && *++surname != '\0') {
        char temp_char = encode(*surname);
        if (encode(*surname) != encode(previous_character) && temp_char != '0') {
            soundex[soundex_pos] = temp_char;
            previous_character = *surname;
            soundex_pos++;
        }
    }

    while (*surname == '\0' & soundex_pos < 4) {
        soundex[soundex_pos++] = '0';
    }
}


int compare(const char* one, const char* two) {
    if (strlen(one) == 0 && strlen(two) == 0) {
        return true;
    }
    if (*one != *two) {
        return false;
    }
    return compare(one+1, two+1);
}

int count(const char* const surname, const char* const sentence) {
    char surname_encoding[5];
    encode(surname, surname_encoding);
    
    int same_encoding_count = 0;
    
    int start = 0;
    int end = start;

    while (sentence[start] != '\0') {
        if (!isalpha(sentence[start])) {
            start++;
            continue;
        }

        end = start;
        while (isalpha(sentence[end + 1])) {
            end++;
        }
        // get index of first non alpha char.
        char* first_word = new char[2+end-start];
        strncpy(first_word, sentence+start, 1+end-start);
        first_word[1+end-start] = '\0';
        char encoding[5];
        encode(first_word, encoding);
        if (compare(surname_encoding, encoding)) {
            ++same_encoding_count;
        }
        delete [] first_word;
        start = end + 1;
    }
    
    return same_encoding_count;
}