#include <iostream>
using namespace std;

// Class to represent a distance
class Distance {
private:
    int feet;
    int inches;

public:
    // Default constructor
    Distance() : feet(0), inches(0) {}

    // Parameterized constructor
    Distance(int ft, int in) {
        feet = ft;
        inches = in;
        normalize(); // Ensure inches are less than 12
    }

    // Function to normalize the distance (convert inches to feet if >= 12)
    void normalize() {
        feet += inches / 12;
        inches = inches % 12;
    }

    // Overloading the binary + operator
    Distance operator+(const Distance &d) {
        Distance result;
        result.feet = this->feet + d.feet;
        result.inches = this->inches + d.inches;
        result.normalize(); // Normalize the result
        return result;
    }

    // Function to display the distance
    void display() const {
        cout << feet << " feet, " << inches << " inches" << endl;
    }
};

int main() {
    // Create two Distance objects
    Distance d1(5, 8);  // 5 feet 8 inches
    Distance d2(3, 11); // 3 feet 11 inches

    // Add the two distances using the overloaded + operator
    Distance d3 = d1 + d2;

    // Display the result
    cout << "First Distance: ";
    d1.display();

    cout << "Second Distance: ";
    d2.display();

    cout << "Total Distance: ";
    d3.display();

    return 0;
}
