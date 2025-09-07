#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> adjList[n + 1];
    // 1 based indexing is assumed
    for (int i = 1; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    for (int i = 0; i <= n; i++)
    {
        cout << i << " -> { ";
        for (int j = 0; j < adjList[i].size(); j++)
        {
            cout << adjList[i][j] << " , ";
        }
        cout << "} " << endl;
    }

    return 0;
}