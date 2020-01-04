#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    const char* input = "Hello World";
    char* sentence = new char[strlen(input)];
    strcpy(sentence, input);
    char* token = strtok(sentence, " ");
    while (token != NULL) {
        std::cout << token << std::endl;
        token = strtok(NULL, " ");
    }

    return 0;
}

