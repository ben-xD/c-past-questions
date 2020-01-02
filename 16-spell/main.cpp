#include <iostream>
#include "spell.h"

using namespace std;

int main() {

  cout << "====================== Question 1 ======================" << endl << endl;

  cout << "The frequency of the word 'a' in the corpus is " << frequency("a") << endl;
  
  cout << "The frequency of the word 'the' in the corpus is " << frequency("the") << endl;

  cout << "The frequency of the word 'bicycle' in the corpus is " << frequency("bicycle") << endl;

  cout << "The frequency of the word 'quintessential' in the corpus is " << frequency("quintessential") << endl;

  cout << "The frequency of the word 'nonexistential' is " << frequency("nonexistential") << endl;

  cout << endl;
    
  cout << "====================== Question 2 ======================" << endl << endl;

  cout << "The edit distance between 'an' and 'na' is " << edit_distance("an","na") << endl;

  cout << "The edit distance between 'spelling' and 'spelling' is " << edit_distance("spelling","spelling") << endl;
  
  cout << "The edit distance between 'speling' and 'spelling' is " << edit_distance("speling","spelling") << endl;

    cout << "The edit distance between 'speling' and 'a' is " << edit_distance("speling","a") << endl;
  
  cout << "The edit distance between 'peotryy' and 'poetry' is " << edit_distance("peotryy","poetry") << endl;

  cout << "The edit distance between 'korrectud' and 'corrected' is " << edit_distance("korrectud","corrected") << endl;

  cout << "The edit distance between 'nonexistential' and 'nonexistent' is " << edit_distance("nonexistential","nonexistent") << endl;

  cout << endl;
  
  cout << "====================== Question 3 ======================" << endl << endl;

  char fixed[MAX_LENGTH];

  bool corrected = spell_correct("poetry", fixed);
  cout << "The corrected spelling of 'poetry' is '"<< fixed << "'" << endl;
  cout << "The spell checker was " << (corrected ? "" : "NOT ") << "needed."<< endl <<endl;
  
  corrected = spell_correct("thay", fixed);
  cout << "The corrected spelling of 'thay' is '"<< fixed << "'" << endl;
  cout << "The spell checker was " << (corrected ? "" : "NOT ") << "needed."<< endl <<endl;

  corrected = spell_correct("korrectud", fixed);
  cout << "The corrected spelling of 'korrectud' is '"<< fixed << "'" << endl;
  cout << "The spell checker was " << (corrected ? "" : "NOT ") << "needed."<< endl <<endl;

  corrected = spell_correct("nonexistential", fixed);
  cout << "The corrected spelling of 'nonexistential' is '"<< fixed << "'" << endl;
  cout << "The spell checker was " << (corrected ? "" : "NOT ") << "needed."<< endl <<endl;
  /*  
  cout << "=================== Bonus Question =====================" << endl << endl;
  cout << "The edit distance between 'an' and 'na' is " << edit_distance_bonus("an","na") << endl;

  cout << "The edit distance between 'spelling' and 'spelling' is " << edit_distance_bonus("spelling","spelling") << endl;
  
  cout << "The edit distance between 'speling' and 'spelling' is " << edit_distance_bonus("speling","spelling") << endl;

    cout << "The edit distance between 'speling' and 'a' is " << edit_distance_bonus("speling","a") << endl;

  cout << "The edit distance between 'peotryy' and 'poetry' is " << edit_distance_bonus("peotryy","poetry") << endl;

  cout << "The edit distance between 'korrectud' and 'corrected' is " << edit_distance_bonus("korrectud","corrected") << endl;

  cout << "The edit distance between 'nonexistential' and 'nonexistent' is " << edit_distance_bonus("nonexistential","nonexistent") << endl;

  */
  
  return 0;
}
