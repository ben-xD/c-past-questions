#ifndef _SOUNDEX_H_
#define _SOUNDEX_H_

void encode(const char* surname, char* soundex);
int compare(const char* one, const char* two);
int count(const char* const surname, const char* const sentence);

#endif // _SOUNDEX_H_