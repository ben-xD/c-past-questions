#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
#include <fstream>

using namespace std;

#include "sonnet.h"

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

/* START WRITING YOUR FUNCTION BODIES HERE */
int count_words(const char* line) {
  int count = 1;
  char output[100];
  while (get_word(line, count, output)) {
    count++;
  }
  return count-1;
}

bool find_phonetic_ending(const char* word, char* ending) {
  // open file, iterate line by line for word
  std::ifstream file;
  file.open("dictionary.txt");
  *ending='\0';

    // initial set to 100, but supercalifragislistic... is 114. 
    // this line was found using `awk '{print length, $0}' dictionary.txt |sort -nr|head -1`
  char line[200];
  while(!file.fail()) {
    file.getline(line, 200);
    // check first word is word.
    char first_word[200];
    get_word(line, 1, first_word);
    if (strcmp(word, first_word)) {
      continue; // not the same word.
    }

    int count = count_words(line);
    // Get last vowel phoneme
    int last_vowel_phoneme = 0;
    char phoneme[100];
    for (last_vowel_phoneme = count; last_vowel_phoneme > 0; last_vowel_phoneme--) {
      get_word(line, last_vowel_phoneme, phoneme);
      if (word_contains_vowel(phoneme)) {
        break;
      }
    }

    // Save all phonemes after last_vowel_phoneme, inclusive
    while (last_vowel_phoneme <= count) {
      get_word(line, last_vowel_phoneme, phoneme);
      strcat(ending, phoneme);
      last_vowel_phoneme++;
    }

    return true;
  }
  return false;
}

bool word_contains_vowel(const char* word) {
  for (size_t i = 0; i < strlen(word); i++) {
    if (is_vowel(word[i])) {
      return true;
    }
  }
  return false;
}

bool is_vowel(char c) {
  return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

bool find_rhyme_scheme(const char* filename, char* scheme) {
  std::ifstream file;
  file.open(filename);
  if (!file.good()) {
    return false;
  }

  *scheme = '\0';
  rhyming_letter(RESET);
  char line[512];

  while (file.good()) {
    file.getline(line, 512);
    // count words
    int count = count_words(line);
    // get last word 
    char last_word[512];
    get_word(line, count, last_word);
    if (strlen(last_word) == 0) {
      continue;
    }

    // find phonetic ending for line in file
    char ending[512];
    find_phonetic_ending(last_word, ending);
    
    // save
    char letter[2];
    letter[0] = rhyming_letter(ending);
    letter[1] = '\0';
    strcat(scheme, letter);
  }

  return true;
}