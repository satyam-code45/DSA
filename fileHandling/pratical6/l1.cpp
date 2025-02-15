#include<iostream>
using namespace std;
class Base{
    protected:
    int protectedData = 30;
    public:
    void showbase(){
        cout<<"base class protected data:"<< protectedData<<endl;
    }
};
class Derived: public Base{
    public:
        void showDerived(){
            cout<<"Derived class protected data:"<< protectedData<<endl;
        }
};
int main(){
    Derived d;
    d.showDerived();
    d.showbase();
    return 0;
}