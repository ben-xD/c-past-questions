#include "words.h"
#include <iostream>
#include <string.h>
#include <cctype>

void reverse(const char* str1, char* str2) {
    int str1_length = strlen(str1);
    for (int i = 0; i < str1_length; i++) {
        str2[i] = str1[str1_length - 1 - i];
    }
}

int compare(const char* str1, const char* str2) {
    while (!isalpha(*str1) && *str1 != '\0') {
        str1++;
    }
    while(!isalpha(*str2) && *str2 != '\0') {
        str2++;
    }
    if (*str1 == '\0' && *str2 == '\0') {
        return 1;
    }
    if (tolower(*str1) == tolower(*str2)) {
        return compare(str1 + 1, str2 + 1);
    }
    return 0;
}


int palindrome(const char* str) {
    // reverse, and compare to itself
    char* reversed = new char[strlen(str) + 1];
    reverse(str, reversed);
    reversed[strlen(str)] = '\0';
    int result = compare(str, reversed);
    delete [] reversed;
    return result;
}

// Bubble sort: the first element in list, is compared with each element in the list, it is moved if its bigger. Repeated n-times, where n is the list size. 
void sort(char* str1) {
    for (int iter = 0; iter < strlen(str1); iter++) {
        for (int i = 0; i < strlen(str1) - 1; i++) {
            if (str1[i] > str1[i+1]) {
                int temp = str1[i];
                str1[i] = str1[i+1];
                str1[i+1] = temp;
            }
        }
    }
}

// selection sort: pick the smallest in the unsorted list, and put it last in the sorted list.

// insertion sort: pick the first (or random) element in unsorted list, and insert in the right place.

// merge sort: 

// quick sort

int anagram(const char* str1, const char* str2) {
    // sort characters in both
    char* str1_sorted = new char[strlen(str1)];
    strcmp(str1_sorted, str1);
    char* str2_sorted = new char[strlen(str2)];
    strcmp(str2_sorted, str2);
    
    sort(str1_sorted);
    sort(str2_sorted);
    
    // compare

    int not_equal = compare(str1_sorted, str2_sorted);
    delete [] str1_sorted;
    delete [] str2_sorted;
    return !not_equal;
}
