#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary);

/* converts a binary string representation into a character */
char binary_to_ascii(char *binary);

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(const char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */
void text_to_binary(const char* text, char* binary) {
  if (strlen(text)) {
    ascii_to_binary(text[0], binary);
    text_to_binary(text + 1, binary + 8);
  }
  return;
}

void binary_to_text(const char* binary, char* text) {
  if (strlen(binary)) {
    char ascii[9];
    ascii[8] = '\0'; 
    strncpy(ascii, binary, 8);
    text_to_binary(ascii, text);
    binary_to_text(binary + 8, text + 1);
  }
}

char parity(int a, int b, int c, int d = 0) {
  // if odd, then 1. else 0.
  return (a + b + c) % 2 ? '1' : '0';
}

void add_error_correction(const char* bits, char* text) {
  if (strlen(bits)) {
    // for every 4 chars in bits: save into 7 chars of text
    // calculate check bits
    char c1 = parity(bits[0], bits[1], bits[3]);
    char c2 = parity(bits[0], bits[2], bits[3]);
    char c3 = parity(bits[1], bits[2], bits[3]);

    // 4 bits = 1 segment
    char corrected_segment[8] = {c1, c2, bits[0], c3, bits[1], bits[2], bits[3], '\0'};
    strcpy(text, corrected_segment);
    add_error_correction(bits + 4, text + 7);
  }
  return;
  // interleave check bits
}

int decode(const char* bits, char* text) {
  if (strlen(bits)) {
    // calc parities
    char p1 = parity(bits[3], bits[4], bits[5], bits[6]);
    char p2 = parity(bits[1], bits[2], bits[5], bits[6]);
    char p3 = parity(bits[0], bits[2], bits[4], bits[6]);

      char temp_bits[8];
      temp_bits[7] = '\0';
      strncpy(temp_bits, bits, 7);

    int error_count = (p1 - '0') + (p2 - '0') + (p3 - '0');
    if (error_count != 0) {
    // fix errors
      int bit_error_position = (p1-'0')*4 + (p2-'0')*2 + (p3-'0') - 1;
      temp_bits[bit_error_position] = temp_bits[bit_error_position] == '0' ? '1' : '0';
      // std::cout << '\0' << temp_bits << std::endl;
    }

    // copy characters in from temp_bits
    char binary_text[5];
    binary_text[4] = '\0';
    binary_text[0] = temp_bits[2];
    binary_text[1] = temp_bits[4];
    binary_text[2] = temp_bits[5];
    binary_text[3] = temp_bits[6];

    strcpy(text, binary_text);
    
    return (error_count > 0) + decode(bits + 7, text + 4);
  }
}