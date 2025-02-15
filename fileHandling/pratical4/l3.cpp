#include <iostream>
using namespace std;

// Class to represent a complex number
class Complex {
private:
    float real;   // Real part
    float imag;   // Imaginary part

public:
    // Constructor to initialize complex number
    Complex(float r = 0, float i = 0) {
        real = r;
        imag = i;
    }

    // Overload the binary + operator
    Complex operator+(const Complex &c) {
        return Complex(real + c.real, imag + c.imag); // Add real and imaginary parts
    }

    // Function to display the complex number
    void display() const {
        if (imag >= 0)
            cout << real << " + " << imag << "i" << endl;
        else
            cout << real << " - " << -imag << "i" << endl;
    }
};

int main() {
    // Create two Complex objects
    Complex c1(3.5, 2.5); // 3.5 + 2.5i
    Complex c2(1.5, -1.5); // 1.5 - 1.5i

    // Add the two complex numbers using the overloaded + operator
    Complex c3 = c1 + c2;

    // Display the results
    cout << "First Complex Number: ";
    c1.display();

    cout << "Second Complex Number: ";
    c2.display();

    cout << "Sum of Complex Numbers: ";
    c3.display();

    return 0;
}
