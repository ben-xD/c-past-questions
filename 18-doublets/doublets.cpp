#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */

bool valid_step(const char* current, const char* next) {
  if (strlen(current) != strlen(next)) {
    return false;
  }

  int count = 0;
  for (size_t i = 0; i < strlen(current); i++) {
    if (current[i] != next[i]) {
      count++;
    }
  }

  if (count != 1) {
    return false;
  }

  return true;
}

bool display_chain(const char** chain, std::ostream& output) {
  int length = 0;
  const char** starting_position = chain;
  while (*chain != NULL) {
    length++;
    chain++;
  }
  chain = starting_position;
  
  int index = 0;
  while (*chain != NULL) {
    if (output.good()) {
      if (index == 0 || index == length - 1) {
        output << *chain << '\n';
      } else {
        char* modified_word = new char[strlen(*chain)];
        for (int i = 0; i < strlen(*chain); i++) {
          const char* word = *chain;
          modified_word[i] = tolower(word[i]);
        }
        output << modified_word << std::endl;
        delete[] modified_word;
      }
    } else {
      return false;
    }
    index++;
    chain++;
  }
  return true;
}

bool valid_chain(const char** chain) {
  while (*chain != NULL) {
    if (*(chain+1) != NULL && !valid_step(*chain, *(chain+1))) {
      return false;
    }
    chain++;
  }
  return true;
}

bool find_chain(const char* start, const char* end, const char** answer_chain, int max_steps, int index) {
  if (index == 0) {
    char* first_word = new char[strlen(start)];
    strcpy(first_word, start);
    answer_chain[0] = first_word;
    answer_chain[1] = NULL;
  }
  if (!dictionary_search(start)) {
    return false;
  }
  if (!valid_chain(answer_chain)) {
    return false;
  }
  if (max_steps < 0) {
    return false;
  }
  if (!strcmp(start, end)) {
    return true;
  }

  // create an editable word
  char* word = new char[strlen(start)];
  strcpy(word, start); 

  // edit one char at a time, from 'A' to 'Z'
  for (size_t char_index = 0; char_index < strlen(start); char_index++) {
    char initial_character = word[char_index];
    for (int new_char = 'A'; new_char <= 'Z'; new_char++) {
      word[char_index] = new_char;
      answer_chain[index + 1] = word;
      answer_chain[index + 2] = NULL;
      if (find_chain(word, end, answer_chain, max_steps - 1, index + 1)) {
        return true;
      }
    }
    word[char_index] = initial_character; // reset word
    answer_chain[index + 1] = NULL;
  }
  return false;
}