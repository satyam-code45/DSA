#include <iostream>
using namespace std;

class Factorial {
private:
    int number;
    long long result;

public:
    // Constructor to initialize the number and calculate factorial
    Factorial(int num) {
        number = num;
        result = 1;
        for (int i = 1; i <= number; ++i) {
            result *= i;
        }
    }

    // Copy constructor to create a new object from an existing one
    Factorial(const Factorial &obj) {
        number = obj.number;
        result = obj.result;
    }

    // Function to display the factorial result
    void display() {
        cout << "Factorial of " << number << " is " << result << endl;
    }
};

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;

    // Create an object of Factorial and calculate factorial
    Factorial fact1(num);
    fact1.display();

    // Using copy constructor to create a copy of the object
    Factorial fact2(fact1);
    fact2.display();

    return 0;
}
