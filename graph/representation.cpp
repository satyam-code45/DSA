#include<iostream>
using namespace std;
#include<vector>

int main(){
    //using adjacency matrix
    // int n,m;
    // cin>>n>>m;
    // int adj[n+1][m+1];
    // for(int i=0; i<m; i++){
    //     int u,v;
    //     cin>>u>>v;
    //     adj[u][v] = 1;
    //     adj[v][u] = 1;
    // }
    //adjacency list
    int n,m;
    cin>>n>>m;
    vector<int> adj[n+1];
    for(int i=0; i<m; i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u); //in case of directed graph v is connected to u but u is not connected so this line will be removed
    }
    return 0;
}