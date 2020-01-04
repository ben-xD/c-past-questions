/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

struct Node {
      int value;
      Node* next;
      
      Node(int value, Node* next) {
          this->next = next;
          this->value = value;
      }
};

void initialise_list(Node*& front, Node*& rear) {
    front = NULL;
    rear = NULL;
}

void add_to_front(Node*& front, Node*& rear, int value) {
    if (front == NULL && rear == NULL) {
        front = rear = new Node(value, NULL);
    
    } else {
        Node* old_front = front;
        front = new Node(value, old_front);
    }

}

void add_to_rear(Node*& front, Node*& rear, int value) {
    if (front == NULL && rear == NULL) {
        front = rear = new Node(value, NULL);
    } else {
        Node* old_rear = rear;
        old_rear->next = rear = new Node(value, NULL);
    }
}

std::ostream& operator<<(std::ostream& stream, const Node* list) {
    while (list != nullptr) {
        stream << list->value << ", ";
        list = list->next;
    }
    stream << std::endl;
}

// TO IMPLEMENT:
// delete Node

// add sorted

// delete list

int main()
{
    Node* front;
    Node* rear;
    
        
    initialise_list(front, rear);
    add_to_front(front, rear, 5);
    add_to_front(front, rear, 50);
    add_to_rear(front, rear, 20);
    std::cout << front;

    return 0;
}

