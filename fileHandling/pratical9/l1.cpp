#include <iostream>
#include <fstream> // Required for file handling
using namespace std;

int main() {
    // Declare an ofstream object to write to a file
    ofstream outFile("newfile.txt"); // Creates or opens the file "newfile.txt"

    // Check if the file was successfully opened
    if (!outFile) {
        cerr << "Error: Unable to create or open the file." << endl;
        return 1; // Exit with an error code
    }

    // Write text to the file
    outFile << "Hello, World 1234!" << endl;
    outFile << "This is a sample text written to the file." << endl;

    // Close the file
    outFile.close();

    cout << "File created and text written successfully!" << endl;

    return 0; // Exit the program
}
