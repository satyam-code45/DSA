#include<iostream>
using namespace std;
class Overloading{
    private:
        int feet;
        int inches;
    public:
        Overloading(){
            feet = 0;
            inches = 0;
        }
        Overloading(int feet, int inches){
            this->feet = feet;
            this->inches = inches;
            normalize();
        }
        void normalize(){
            feet += inches/12;
            inches = inches%12;
        }
        Overloading operator+(const Overloading &o){
            Overloading res;
            res.feet += this->feet + o.feet;
            res.inches += this->inches + o.inches;
            res.normalize();
            return res;
        }
        void show(){
            cout<<feet<<" feet  "<<inches<<" inches"<<endl;
        }
};
int main(){
    Overloading o1(2,3);
    Overloading o2(6,10);
    Overloading o3 = o1+o2;
    o1.show();
    o2.show();
    o3.show();
}