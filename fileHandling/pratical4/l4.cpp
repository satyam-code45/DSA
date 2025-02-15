#include<iostream>
using namespace std;
class Calculator
{
private:
    float real;
    float imag;
public:
    Calculator(){
        real = 0;
        imag = 0;
    }
   Calculator(float real, float imag){
        this->real = real;
        this->imag = imag;
   }
   Calculator operator +(const Calculator &c){
        Calculator res;
        res.real = this->real + c.real;
        res.imag = this->imag + c.imag;
        return res;
   }
   void show(){
        cout<<endl;
        cout<<real<<"+"<<imag<<endl;
   }
};
int main(){
    Calculator c1(3.3,2.0);
    Calculator c2(1.0,4.0);

    Calculator c3 = c1+c2;
    c1.show();
    c2.show();
    c3.show();
    return 0;
}


