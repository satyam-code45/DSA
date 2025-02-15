#include<iostream>
#include<fstream>
using namespace std;
int main(){
    fstream file("newfile.txt");
    fstream destfile("destination.txt");
    if (!file)
    {
        cout<<"File not opened"<<endl;
        return 1;
    }
    int lineCount = 0;
    string line;
    while (getline(file, line)){
        cout<<line<<endl;
        destfile<<line<<endl;
        lineCount++;
    }
    destfile.close();
    cout<<"Total line: "<< lineCount <<endl;
    file.close();
    fstream wordfile("newfile.txt");
    int wordCount = 0;
    string word;
    while (wordfile >> word)
    {
        wordCount++;
    }
    cout<<"Total word: "<< wordCount <<endl;
    wordfile.close();
    return 0;
}