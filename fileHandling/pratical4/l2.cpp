#include<iostream>
using namespace std;
class Coordinate{
private:
    int x;
    int y;
    int z;
public:
    Coordinate(){
        x = 0;
        y= 0;
        z = 0;
    }
    Coordinate(int a, int b, int c){
        x = a;
        y = b;
        z = c;
    }
    Coordinate operator-(){
        Coordinate res;
        res.x = -x;
        res.y = -y;
        res.z = -z;
        return res;
    }
    void show(){
        cout<<"("<<x<<","<<y<<","<<z<<")"<<endl;
    }
};
int main(){
    Coordinate c1(2,-1,3);
    c1.show();
    c1 = -c1;
    c1.show();
    return 0;
}