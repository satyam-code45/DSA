#include<iostream>
using namespace std;
int fib(int n) {
    if(n <= 1) return n;
    int c = fib(n-1) + fib(n-2);
    return c;
}
int main(){
    int n;
    cout<<"Enter n: ";
    cin>>n;
    cout<< "fib( "<<n<<" ) = ";
    cout<<fib(n)<<endl;
    return 0;
}