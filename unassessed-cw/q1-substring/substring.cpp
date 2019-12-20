#include "substring.h"
#include "cstring"

bool is_prefix(const char* string1, const char* string2) {
    if (strlen(string1) == 0) {
        return true;
    }
    if (*string1 != *string2) {
        return false;
    } 
    return is_prefix(string1+1, string2+1);
}

int substring_position(const char* substring, const char* string) {
    // iterate over every character of string, to see if substring is a prefix
    for (size_t i = 0; i < strlen(string); i++) {
        if (is_prefix(substring, string + i))
        {
            return i;
        }
    }
    return -1;
}