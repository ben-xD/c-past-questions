#include <iostream>
#include <memory>
#include <cstring>

std::unique_ptr<char[]> quicksort(const char* sentence);

int main() {
    char* sentence = "My name is bob.";
    std::cout << sentence << std::endl;

    std::unique_ptr<char[]> sorted = quicksort(sentence);

    
    
    std::cout << sorted << std::endl;
}

std::unique_ptr<char[]> quicksort(const char* sentence){
    auto sorted = std::make_shared<char[]>(strlen(sentence));
    strcpy(sorted.get(), sentence);

    // get pivot (median of first, last and middle digit)
    get_mid(sorted, )
    // 

    
    return sorted;
}