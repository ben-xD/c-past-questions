#include <iostream>
#include <cctype>
#include "playfair.h"

using namespace std;

int main() {

  // question 1 

  cout << "====================== Question 1 ======================" << endl;

  char prepared[100];
  prepare("Come to the Queen's Tower at 7 o'clock!",prepared);

  cout << "'Come to the Queen's Tower at 7 o'clock!' has been prepared for ";
  cout << "encoding as:" << endl;
  cout << "'" << prepared << "'." << endl << endl;

  // question 2  

  cout << "====================== Question 2 ======================" << endl;

  char playfair[6][6];
  grid("IMPERIAL",playfair);

  cout << "The encoding grid corresponding to the codeword 'IMPERIAL' is:" << endl;
  for (int row=0; row<6; row++) {
    for (int col=0; col<6; col++) 
      cout << ((isalnum(playfair[row][col])) ? playfair[row][col] : '?') << ' ';
    cout << endl;
  }
  cout << endl;

  // question 3

  cout << "====================== Question 3 ======================" << endl;

  char out1, out2;
  bigram(playfair,'C','O',out1,out2);

  cout << "The bigram 'CO' encodes as '" << out1 << out2 << "'" << endl;

  bigram(playfair,'N','9',out1,out2);

  cout << "The bigram 'N9' encodes as '" << out1 << out2 << "'" << endl << endl;

  // question 4
  cout << "====================== Question 4 ======================" << endl;

  char encoded[100];
  encode(playfair, prepared, encoded);

  cout << "The string '" << prepared << "' encodes as:" << endl;
  cout << "'" << encoded << "'" << endl << endl;

  // bonus question (uncomment to attempt)

  /*
  cout << "==================== Bonus Question ====================" << endl;

  char decoded[100];
  decode(playfair,"VEKVPDQIQDEDEMMVEHSJPVHENOGMIRHVVMEG",decoded);

  cout << "The string 'VEKVPDQIQDEDEMMVEHSJPVHENOGMIRHVVMEG' decodes as:" << endl;
  cout << "'" << decoded << "'" << endl;
  */
 
  return 0;
}
