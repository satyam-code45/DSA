#include <iostream>
using namespace std;

// Base class
class Base {
public:
    // Virtual function to allow overriding in the derived class
    virtual void display() {
        cout << "Display function of Base class" << endl;
    }
};

// Derived class
class Derived : public Base {
public:
    // Overriding the display function of the Base class
    void display() override {
        cout << "Display function of Derived class" << endl;
    }
};

int main() {
    Base baseObj;       // Object of Base class
    Derived derivedObj; // Object of Derived class

    Base *ptr; // Pointer to Base class

    // Pointing to Base class object
    ptr = &baseObj;
    cout << "Using Base class pointer to Base object:" << endl;
    ptr->display();

    // Pointing to Derived class object
    ptr = &derivedObj;
    cout << "Using Base class pointer to Derived object:" << endl;
    ptr->display();

    return 0;
}
