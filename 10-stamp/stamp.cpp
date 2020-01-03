#include <iostream>
#include <openssl/sha.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <fstream>
#include <limits>
#include "stamp.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

// helper function for internal use only
// transforms raw binary hash value into human-friendly hexademical form
void convert_hash(const unsigned char *str, char *output, int hash_length) {
  char append[16];
  strcpy (output, "");
  for (int n=0; n<hash_length; n++) {
    sprintf(append,"%02x",str[n]);
    strcat(output, append);
  }
}

// pre-supplied helper function
// generates the SHA1 hash of input string text into output parameter digest
// ********************** IMPORTANT **************************
// ---> remember to include -lcrypto in your linking step <---
// ---> so that the definition of the function SHA1 is    <---
// ---> included in your program                          <---
// ***********************************************************
void text_to_SHA1_digest(const char *text, char *digest) {
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1( (const unsigned char *) text, strlen(text), hash);
  convert_hash(hash, digest, SHA_DIGEST_LENGTH);
}

/* add your function definitions here */
int leading_zeros(const char* digest) {
  int count = 0;
  bool is_leading_zero = true;

  while (strlen(digest)) {
    if (*digest == '0' && is_leading_zero) {
      count++;
    } else {
      is_leading_zero = false;
    }
    if (!isxdigit(*digest)) {
      return -1;
    }
    digest++;
  }
  return count;
}

bool file_to_SHA1_digest(const char* filename, char* digest) {
  std::ifstream file;
  file.open(filename);
  
  if (!file.good()) {
    strcpy(digest, "error");
    return false;
  }
  
  // TODO
  // read entire file. how??
  // didnt know how to do this without SO
  file.seekg(0, file.end);
  int size = file.tellg();
  file.seekg(0, file.beg);
  char* contents = new char[size];

  file.read(contents, size);
  // std::cout << contents << std::endl;
  
  text_to_SHA1_digest(contents, digest);
  file.close();
  delete contents;
  return true;
}

bool make_header(const char* recipient, const char* filename, char* header) {
  char digest[41];
  bool success_digest = file_to_SHA1_digest(filename, digest);
  if (!success_digest) {
    return false;
  }
  
  // try up to 10 million
  for (int counter = 0; counter < 10000000; counter++) {
    // use counter to create header
    // convert counter to string
    // email:digest:counter
    strcpy(header, recipient);
    strcpy(header + strlen(recipient), ":");
    strcpy(header + strlen(recipient) +  1, digest);
    strcpy(header + strlen(recipient) + 1 + strlen(digest), ":");
    sprintf(header + strlen(recipient) + 1 + strlen(digest) + 1, "%d", counter);
    
    //, hash header
    char header_digest[41];
    text_to_SHA1_digest(header, header_digest);
    if (leading_zeros(header_digest) >= 5) {
      return true;
    }
  }
  return false;
}

MessageStatus check_header(const char* email, const char* header, const char* filename) {
  // confirm format (2 colons, 3 fields)
  char received_recipient[512];
  char received_digest[41];

  char* tokenizing_header = new char[strlen(header)];
  strcpy(tokenizing_header, header);
  char* token = strtok(tokenizing_header, ":");
  if (token) {
    strcpy(received_recipient, token);
  }

  token = strtok(NULL, ":");
  if (token) {
    strcpy(received_digest, token);
  }

  token = strtok(NULL, ":");
  token = strtok(NULL, ":");
  delete tokenizing_header;
  if (token != NULL) {
    return INVALID_HEADER;
  }

  if (strcmp(received_recipient, email)) {
    return WRONG_RECIPIENT;
  }

  char digest[41];
  bool success = file_to_SHA1_digest(filename, digest);
  if (!success || strcmp(digest, received_digest)) {
    return INVALID_MESSAGE_DIGEST;
  }

  char header_digest[41];
  text_to_SHA1_digest(header, header_digest);
  if (leading_zeros(header_digest) < 5) {
    return INVALID_HEADER_DIGEST;
  }
  
  return VALID_EMAIL;
}