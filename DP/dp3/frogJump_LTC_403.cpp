#include<iostream>
#include<vector>
using namespace std;


    bool canCross(vector<int>& stones) {
        int k = 1;
        if((stones[0] + k ) != stones[1]) return false;
        for(int i =1; i<stones.size(); i++){
            cout<<"loop = "<<i<<endl;
            if((stones[i] + k) == stones[i+1]){
                cout<<"if1"<<endl;
                continue;
            } 
            else if((stones[i] + (k+1)) == stones[i+1]) {
                cout<<"if2"<<endl;
                k++;
                continue;
            }
            else if((stones[i] + (k-1)) == stones[i+1]) {
                cout<<"if2"<<endl;
                k--;
                continue;
            }
            
            else {
                cout<<"else = "<<i<<endl;
                return false;
            }
        } 

        return true;
    }


int main(){
    vector<int>stones{0,1,3,5,6,8,12,17};
    cout<<canCross(stones)<<"  = boolans "<<endl;
    cout<<"done"<<endl;
}