#include<iostream>
#include<ctime>
using namespace std;
class Time{
    public:
    Time(){
        time_t now = time(0);
        cout<<"Current Date and Time: "<<ctime(&now);
    }
};
int main(){
    Time t;
    return 0;
}