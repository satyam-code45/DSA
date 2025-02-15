#include <iostream>
using namespace std;

// Base class
class Parent {
public:
    void showParentMessage() {
        cout << "This is a message from the Parent class." << endl;
    }
};

// Derived class inheriting from the Parent class
class Child : public Parent {
public:
    void showChildMessage() {
        cout << "This is a message from the Child class." << endl;
    }
};

int main() {
    // Create an object of the Child class
    Child childObject;

    // Access methods from both the Parent and Child classes
    childObject.showParentMessage(); // Inherited from Parent
    childObject.showChildMessage(); // Defined in Child

    return 0;
}
