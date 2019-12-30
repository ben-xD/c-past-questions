#include <iostream>
#include <cctype>
#include <fstream>
#include "piglatin.h"

using namespace std;

int main() {

  /* QUESTION 1 */

  cout << "====================== Question 1 ======================" << endl;

  int vowel;

  vowel = findFirstVowel("Passionfruit");
  cout << "The first vowel in 'Passionfruit' occurs at position " << vowel << endl;

  vowel = findFirstVowel("prune");
  cout << "The first vowel in 'prune' occurs at position " << vowel << endl;

  vowel = findFirstVowel("my");
  cout << "The first vowel in 'my' occurs at position " << vowel << endl;

  vowel = findFirstVowel("chrysanthemum");
  cout << "The first vowel in 'chrysanthemum' occurs at position " << vowel << endl;
  cout << endl;

  /* QUESTION 2 */

  cout << "====================== Question 2 ======================" << endl;

  char translated[100];

  translateWord("grape", translated);
  cout << "In Pig Latin 'grape' is '" << translated << "'." << endl;
  translateWord("orange", translated);
  cout << "In Pig Latin 'orange' is '" << translated << "'." << endl;
  translateWord("Banana", translated);
  cout << "In Pig Latin 'Banana' is '" << translated << "'." << endl;
  translateWord("Yellow", translated);
  cout << "In Pig Latin 'Yellow' is '" << translated << "'." << endl;  
  translateWord("grrr", translated);
  cout << "In Pig Latin 'grrr' is '" << translated << "'." << endl;
  translateWord("apple", translated);
  cout << "In Pig Latin 'apple' is '" << translated << "'." << endl;
    translateWord("crying", translated);
  cout << "In Pig Latin 'crying' is '" << translated << "'." << endl;
    translateWord("strong", translated);
  cout << "In Pig Latin 'strong' is '" << translated << "'." << endl;
   translateWord("300", translated);
  cout << "In Pig Latin '300' is '" << translated << "'." << endl;

  /* QUESTION 3 */
  
  cout << "====================== Question 3 ======================" << endl;

  cout << "The file 'fruit.txt' translated into Pig Latin is:" << endl << endl;
  ifstream input;
  input.open("fruit.txt");
  translateStream(input, cout);
  input.close();
  cout << endl;

  return 0;
}



