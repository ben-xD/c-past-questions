#include <iostream>

int findFirstVowel(const char* word);
bool isVowel(char character, int position, int length);
void translateWord(const char* english, char* piglatin);
void translateStream(std::istream& input, std::ostream& output);