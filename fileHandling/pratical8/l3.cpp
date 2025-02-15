#include <iostream>
using namespace std;

// Base class
class Grandparent {
public:
    void showGrandparentMessage() {
        cout << "This is a message from the Grandparent class." << endl;
    }
};

// Intermediate class (inherits from Grandparent)
class Parent : public Grandparent {
public:
    void showParentMessage() {
        cout << "This is a message from the Parent class." << endl;
    }
};

// Derived class (inherits from Parent)
class Child : public Parent {
public:
    void showChildMessage() {
        cout << "This is a message from the Child class." << endl;
    }
};

int main() {
    // Create an object of the Child class
    Child childObject;

    // Access methods from all levels of inheritance
    childObject.showGrandparentMessage(); // Inherited from Grandparent
    childObject.showParentMessage();      // Inherited from Parent
    childObject.showChildMessage();       // Defined in Child

    return 0;
}
