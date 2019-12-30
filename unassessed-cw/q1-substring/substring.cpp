#include "substring.h"
#include <iostream>
#include "cstring"

bool is_prefix(const char *string1, const char *string2) {
    if (strlen(string1) == 0) {
        return true;
    }
    if (*string1 != *string2) {
        return false;
    }
    return is_prefix(string1 + 1, string2 + 1);
}

// iterative
// int substring_position(const char* substring, const char* string) {
//     // iterate over every character of string, to see if substring is a prefix
//     for (size_t i = 0; i < strlen(string); i++) {
//         if (is_prefix(substring, string + i))
//         {
//             return i;
//         }
//     }
//     return -1;
// }

// recursive
// int substring_position(const char *substring, const char *string) {
//     if (strlen(substring) == 0) {
//         return 0;
//     }
//     if (strlen(string) == 0) {
//         return -1;  // bad: empty, but not substring
//     }
//     // iterate over every character of string, to see if substring is a prefix
//     if (is_prefix(substring, string)) {
//         return 0;
//     }
//     int value = substring_position(substring, string + 1);
//     if (value == -1) {
//         return -1;
//     }
//     return value + 1;
// }


// a challenge for fun
int substring_position(const char *b, const char *s) {
    return strstr(s,b)?strstr(s,b)-s:-1;
}