#include <iostream>
using namespace std;

// Base class 1
class Parent1 {
public:
    void showParent1Message() {
        cout << "This is a message from Parent1." << endl;
    }
};

// Base class 2
class Parent2 {
public:
    void showParent2Message() {
        cout << "This is a message from Parent2." << endl;
    }
};

// Derived class inheriting from both Parent1 and Parent2
class Child : public Parent1, public Parent2 {
public:
    void showChildMessage() {
        cout << "This is a message from the Child class." << endl;
    }
};

int main() {
    // Create an object of the Child class
    Child childObject;

    // Access methods from both Parent1, Parent2, and the Child class
    childObject.showParent1Message(); // Inherited from Parent1
    childObject.showParent2Message(); // Inherited from Parent2
    childObject.showChildMessage();   // Defined in Child

    return 0;
}
