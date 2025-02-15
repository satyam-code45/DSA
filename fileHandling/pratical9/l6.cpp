#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // For handling streams
using namespace std;

int main() {
    // File name
    string fileName = "newfile.txt"; // Replace with your file name

    // Open the file for reading
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Unable to open the file for reading." << endl;
        return 1; // Exit with an error code
    }

    // Read the entire content of the file
    stringstream buffer;
    buffer << inFile.rdbuf(); // Read the file into a buffer
    string content = buffer.str(); // Store content in a string
    inFile.close();

    // Word to find and replace
    string wordToFind = "oldword";    // Replace with the word to find
    string wordToReplace = "newword"; // Replace with the replacement word

    // Find and replace logic
    size_t pos = content.find(wordToFind);
    while (pos != string::npos) {
        content.replace(pos, wordToFind.length(), wordToReplace);
        pos = content.find(wordToFind, pos + wordToReplace.length());
    }

    // Open the file for writing
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Error: Unable to open the file for writing." << endl;
        return 1; // Exit with an error code
    }

    // Write the modified content back to the file
    outFile << content;
    outFile.close();

    cout << "Word replaced successfully!" << endl;

    return 0;
}
