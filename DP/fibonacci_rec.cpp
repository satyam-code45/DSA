#include<iostream>
using namespace std;
int fib(int n) {
    if(n == 0) return 0;
    else if(n == 1) return 1;
    int c = fib(n-1) + fib(n-2);
    return c;
}
int main(){
    cout << "Fibonacci Sequence: ";
    for (int i = 0; i < 5; ++i) {
        cout << fib(i) << " ";
    }
    return 0;
}