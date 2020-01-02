#include <iostream>
#include <cstring>
#include <cassert>
#include "stamp.h"

using namespace std;

// internal helper function for use of Q4 in main() only
const char *message_status(MessageStatus status) {
  switch(status) {
  case INVALID_HEADER:
    return "Invalid header.";
  case WRONG_RECIPIENT:
    return "Wrong recipient.";
  case INVALID_MESSAGE_DIGEST:
    return "Invalid message digest.";
  case INVALID_HEADER_DIGEST:
    return "Invalid header digest.";
  case VALID_EMAIL:
    return "Valid email.";
  }
}

int main()
{
  /* this section illustrates the use of the pre-supplied helper function */
  cout << "============== Pre-supplied functions ==================" << endl << endl;
  
  char digest[41];
  text_to_SHA1_digest("The bitcoin is under the carpet in the living room.", digest);
  cout << "SHA1 digest of message 'The bitcoin is under the carpet in the living room' is:" << endl << digest << endl << endl;

  text_to_SHA1_digest("The bitcoin is under the carpet in the dining room.", digest);
  cout << "SHA1 digest of message 'The bitcoin is under the carpet in the dining room' is:" << endl << digest << endl << endl;
  
  cout << "====================== Question 1 ======================" << endl << endl;

  cout << "The number of leading zeros in digest '60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5' is " << leading_zeros("60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5") << endl << endl;

  cout << "The number of leading zeros in digest '00000a184d72f39730312554e0df25e6f95a05d4' is " << leading_zeros("00000a184d72f39730312554e0df25e6f95a05d4") << endl << endl;

  cout << "The number of leading zeros in digest '000000not-actually-a-hash' is " << leading_zeros("000000not-actually-a-hash") << endl << endl;
  
  cout << "====================== Question 2 ======================" << endl << endl;
  
  strcpy(digest, "");
  bool success = file_to_SHA1_digest("message1.txt", digest);
  cout << "SHA1 digest of file 'message1.txt' is " << digest << endl;
  if (!success)
    cout << "There was an error reading the file." << endl;
  cout << endl;

  strcpy(digest, "");
  success = file_to_SHA1_digest("message2.txt", digest);
  cout << "SHA1 digest of file 'message2.txt' is " << digest << endl;
  if (!success)
    cout << "There was an error reading the file." << endl;
  cout << endl;
  
  strcpy(digest, "");
  success = file_to_SHA1_digest("message3.txt", digest);
  cout << "SHA1 digest of file 'message3.txt' is " << digest << endl;
  if (!success)
    cout << "There was an error reading the file." << endl;
  cout << endl;

  strcpy(digest, "");
  success = file_to_SHA1_digest("doesnotexist.txt", digest);
  cout << "SHA1 digest of file 'doesnotexist.txt' is " << digest << endl;
  if (!success)
    cout << "There was an error reading the file." << endl;
  cout << endl;

  cout << "====================== Question 3 ======================" << endl << endl;
  
  char header[512];
  success = make_header("wjk@imperial.ac.uk", "message1.txt", header);
  if (success)
    cout << "A valid header for 'message1.txt' is "<< endl
	 << header << endl;
  else
    cout << "There was an error generating the header." << endl;
  cout << endl;

  success = make_header("wjk@imperial.ac.uk", "message2.txt", header);
  if (success)
    cout << "A valid header for 'message2.txt' is "<< endl
	 << header << endl;
  else
    cout << "There was an error generating the header." << endl;
  cout << endl;

  success = make_header("wjk@imperial.ac.uk", "message3.txt", header);
  if (success)
    cout << "A valid header for 'message3.txt' is "<< endl
	 << header << endl;
  else
    cout << "There was an error generating the header." << endl;
  cout << endl;

  cout << "====================== Question 4 ======================" << endl << endl;

  // valid email
  cout << "Checking email with header " << endl
       << "'wjk@imperial.ac.uk:60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5:313889'" 
       << endl << "sent to 'wjk@imperial.ac.uk' with body 'message1.txt':" << endl;
  MessageStatus result = check_header("wjk@imperial.ac.uk",
    "wjk@imperial.ac.uk:60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5:313889",
    "message1.txt");
  cout << message_status(result) << endl << endl;

  // wrong recipient
  cout << "Checking email with header " << endl
       << "'wjk@imperial.ac.uk:60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5:313889'"
       << endl << "sent to 'fs@imperial.ac.uk' with body 'message1.txt':" << endl;
  result = check_header("fs@imperial.ac.uk",
    "wjk@imperial.ac.uk:60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5:313889",
    "message1.txt");
  cout << message_status(result) << endl << endl;

  // invalid message digest
  cout << "Checking email with header " << endl
       << "'wjk@imperial.ac.uk:60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5:313889'"
       << endl << "sent to 'wjk@imperial.ac.uk' with body 'message2.txt':" << endl;
  result = check_header("wjk@imperial.ac.uk",
    "wjk@imperial.ac.uk:60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5:313889",
    "message2.txt");
  cout << message_status(result) << endl << endl;

  // wrong counter leading to invalid header digest
  cout << "Checking email with header " << endl
       << "'wjk@imperial.ac.uk:60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5:875231'"
       << endl << "sent to 'wjk@imperial.ac.uk' with body 'message1.txt':" << endl;
  result = check_header("wjk@imperial.ac.uk",
    "wjk@imperial.ac.uk:60eb8db1a3c0ea1ad3d5548f248b4a3e73711ee5:875231",
    "message1.txt");
  cout << message_status(result) << endl << endl;

  return 0;
}
