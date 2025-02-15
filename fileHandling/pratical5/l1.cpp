#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int rollNo;
    float marks;

public:
    // Constructor to initialize student details
    Student(string n, int r, float m) {
        name = n;
        rollNo = r;
        marks = m;
        cout << "Constructor Called: Student object created!" << endl;
    }

    // Display student details
    void displayDetails() {
        cout << "Student Name: " << name << endl;
        cout << "Roll Number: " << rollNo << endl;
        cout << "Marks: " << marks << endl;
    }

    // Destructor
    ~Student() {
        cout << "Destructor Called: Student object destroyed!" << endl;
    }
};

int main() {
    // Create a Student object
    Student student1("John Doe", 101, 89.5);

    // Display student details
    student1.displayDetails();

    return 0;
}
