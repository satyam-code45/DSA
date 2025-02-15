#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Open the source file in read mode
    fstream sourceFile("source.txt"); // Replace "source.txt" with your source file's name
    if (!sourceFile) {
        cerr << "Error: Unable to open the source file." << endl;
        return 1; // Exit with an error code
    }

    // Open the destination file in write mode
    fstream destFile("destination.txt"); // Replace "destination.txt" with your destination file's name
    if (!destFile) {
        cerr << "Error: Unable to open/create the destination file." << endl;
        return 1; // Exit with an error code
    }

    // Copy contents line by line
    string line;
    while (getline(sourceFile, line)) {
        destFile << line << endl; // Write each line to the destination file
    }

    // Close the files
    sourceFile.close();
    destFile.close();

    cout << "Contents copied successfully from source.txt to destination.txt." << endl;

    return 0;
}
