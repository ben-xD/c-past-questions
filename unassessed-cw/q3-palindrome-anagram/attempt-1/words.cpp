#include "words.h"

#include <cctype>
#include <iostream>

// use isalpha(char ch)
// use toupper(char c)

void reverse(const char* str1, char* str2) {
    int size = strlen(str1);
    std::cout << size << std::endl;
    
    for (int i = 0; i <= size; i++)
    {
        str2[i] = str1[size - 1 - i];
    }
    str2[size] = '\0';

    return;
}

int compare(const char* str1, const char* str2) {
    while (!isalpha(*str1) && *str1 != '\0') {
        str1++;
    }
    while (!isalpha(*str2) && *str1 != '\0') {
        str2++;
    }
    if (*str1 == '\0' || *str2 == '\0') {
        return 1;
    }
    if (toupper(*str1) == toupper(*str2)) {
        return compare(str1+1, str2+1);
    }
    return 0;
}

int palindrome(const char *str1){
    int size = strlen(str1);
    char* reversed = new char[size + 1];
    reverse(str1, reversed);
    int result = compare(str1, reversed);
    delete [] reversed;
    return result;
}

int get_min_index_from(const char* str, int position) {
    int min_index = position;
    for (int i = position; i < strlen(str); i++) {
        if (toupper(str[i]) < toupper(str[min_index])) {
            min_index = i;
        }
    }
    return min_index;
}

const char* sort(const char* str) {
    int size = strlen(str);
    char* sorted = new char[size];
    strcpy(sorted, str);
    // in-place sort
    // find smallest value, replace 
    for (int i = 0; i < size; i++) {
        // find smallest value in array. get its index
        int min_index = get_min_index_from(sorted, i);
        // swap 
        char tmp = sorted[i];
        sorted[i] = sorted[min_index];
        sorted[min_index] = tmp;
    }
    return sorted;
}

int anagram(const char* str1, const char* str2) {
    const char* sorted1 = sort(str1);
    const char* sorted2 = sort(str2);
    int result = compare(sorted1, sorted2);
    delete [] sorted1;
    delete [] sorted2;
    return result;
}