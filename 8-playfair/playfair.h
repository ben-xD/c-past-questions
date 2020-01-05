#ifndef _Playfair_h_
#define _Playfair_h_

void prepare(const char* input, char* output);
void grid(const char* codeword, char square[6][6]);
void bigram(char square[6][6], char in1, char in2, char& out1, char& out2);
void encode(char square[6][6], const char* prepared, char* encoded);

#endif // _Playfair_h_