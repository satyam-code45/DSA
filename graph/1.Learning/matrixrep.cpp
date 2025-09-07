#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adjMax(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adjMax[u][v] = 1;
        adjMax[v][u] = 1; // because undirected
    }

    // Print the adjacency matrix
    cout << "Adjacency Matrix:\n";
    for (int i = 0; i <= n; i++) // include 0th row
    {
        for (int j = 0; j <= n; j++) // include 0th column
        {
            cout << adjMax[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
