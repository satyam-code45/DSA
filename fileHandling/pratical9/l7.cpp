#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // File name
    string fileName = "example.txt"; // Replace with your file name

    // Open the file in append mode
    ofstream outFile(fileName, ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open the file for appending." << endl;
        return 1; // Exit with an error code if the file can't be opened
    }

    // Data to append
    string data;
    cout << "Enter the data to append to the file: ";
    getline(cin, data); // Read input from the user

    // Append data to the file
    outFile << data << endl;

    // Close the file
    outFile.close();

    cout << "Data appended successfully to " << fileName << "." << endl;

    return 0;
}
