#include<iostream>
#include<vector>
using namespace std;
int fib(int n, vector<int>dp) {
    if(n <= 1) return n;
    if (dp[n] != -1)
    {
        return dp[n];
    }
    
    dp[n] = fib(n-1, dp) + fib(n-2, dp);
    return dp[n];
}
int main(){
    int n;
    cout<<"Enter n: ";
    cin>>n;
    vector<int>dp(n+1,-1);
    cout<< "fib( "<<n<<" ) = ";
    cout<<fib(n,dp)<<endl;
    return 0;
}