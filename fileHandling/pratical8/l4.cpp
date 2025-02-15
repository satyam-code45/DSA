#include <iostream>
using namespace std;

// Base class
class Parent {
public:
    void showParentMessage() {
        cout << "This is a message from the Parent class." << endl;
    }
};

// Derived class 1 (inherits from Parent)
class Child1 : public Parent {
public:
    void showChild1Message() {
        cout << "This is a message from Child1 class." << endl;
    }
};

// Derived class 2 (inherits from Parent)
class Child2 : public Parent {
public:
    void showChild2Message() {
        cout << "This is a message from Child2 class." << endl;
    }
};

int main() {
    // Create objects of both child classes
    Child1 child1Object;
    Child2 child2Object;

    // Access methods from the Parent class and respective Child classes
    child1Object.showParentMessage();   // Inherited from Parent
    child1Object.showChild1Message();   // Defined in Child1

    child2Object.showParentMessage();   // Inherited from Parent
    child2Object.showChild2Message();   // Defined in Child2

    return 0;
}
