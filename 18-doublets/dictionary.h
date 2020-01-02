/* This header contains a Dictionary class which reads words from a file
   and provides a way for them to be searched. It is used by the helper
   function dictionary_search(...). It should be not necessary for you to study
   this header in any detail during the programming examination itself. */

#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <iostream>
#include <bitset>
#include <cstring>
#include <cassert>
#include <fstream>

/* In the event of restricted memory try a lower number like 86028121 */
#define FILTER_SIZE 982451653

class Dictionary {
private:
  std::bitset<FILTER_SIZE> *bits;

  /* Bob Jenkins' One-at-a-Time Hash Function: Good for hashing strings */
  static unsigned hash(const char *p) 
  {
    unsigned h = 0;
    int i;

    for (i = 0; i < strlen(p); i++) {
        h += p[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h % FILTER_SIZE;
  }

  bool load_dictionary(const char *filename) {
    std::ifstream in(filename);
    if (!in)
      return false;
    char word[512];
    int count = 0;
    for (count = 0; in >> word; count++)
      insert(word);
    in.close();
    return true;
  }

public:
  Dictionary(const char *filename) {
    bits = new (std::nothrow) std::bitset<FILTER_SIZE>;
    assert(bits);
    assert(load_dictionary(filename));
  }

  ~Dictionary() {
    delete bits;
  }
  
  inline void insert(const char *word) {
    bits->set(hash(word));
  }

  inline bool search(const char *word) const {
    return bits->test(hash(word));
  }
};
#endif
