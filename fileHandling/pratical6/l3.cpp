#include<iostream>
using namespace std;
class Base{
    private: 
    int privateData = 40;
    protected:
    int protectedData = 30;
    public:
    int publicData = 50;
    void showbase(){
        cout<<"base class protected data:"<< protectedData<<endl;
        cout<<"base class private data:"<< privateData<<endl;
        cout<<"base class public data:"<< publicData<<endl;
    }
    void displayPrivate(){
        cout<< privateData<<endl;
    }
};
class Derived: public Base{
    public:
        void showDerived(){
            cout<<"Derived class protected data:"<< protectedData<<endl;
            cout<<"Derived class private data:";
            displayPrivate();
            cout<<"Derived class public data:"<< publicData<<endl;
        }
};
int main(){
    Derived d;
    d.showDerived();
    d.showbase();
    return 0;
}