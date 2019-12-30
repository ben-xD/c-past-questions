#include <iostream>

int main() {
    // bubble sort
    int numbers[10] = {0,1,2,3,4,5,6,7};
    // int numbers[10] = {}; // = {0,1,2,3,4,5,6,7};
    for (int i = 0; i < 10; i++) {
        std::cout << numbers[i];
    }
    std::cout << std::endl;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10 - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int tmp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = tmp;
            }
        }
    }
    for (int i = 0; i < 10; i++)
    {
        std::cout << numbers[i];
    }
    std::cout << std::endl;
}