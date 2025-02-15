#include <iostream>
#include <fstream> // Required for file handling
#include <string>  // Required for handling strings
using namespace std;

int main()
{
    // Declare an ifstream object to read from a file
    fstream inFile("newfile.txt"); // Replace "existingfile.txt" with your file's name

    // Check if the file was successfully opened
    if (!inFile)
    {
        cerr << "Error: Unable to open the file." << endl;
        return 1; // Exit with an error code
    }

    cout << "Contents of the file:" << endl;
    int lineCount = 0;
    string line;
    // Read the file line by line and display the contents
    while (getline(inFile, line))
    {
        cout << line << endl; // Output each line to the console
        lineCount++;
    }

    int wordCount = 0;
    string word; // Variable to store each word

    while (inFile >> word)
    {
        wordCount++; // Increment the counter for each word
    }

    // Close the file
    inFile.close();
    
    cout << "The number of lines in the file is: " << lineCount << endl;

    cout << "The number of words in the file is: " << wordCount << endl;

    return 0;
}
