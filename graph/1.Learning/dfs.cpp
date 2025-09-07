#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> adj[], vector<int> &vis, vector<int> &dfsList)
{
    vis[node] = 1;
    dfsList.push_back(node);

    // traverse all its neighbour

    for (auto it : adj[node])
    {
        if (!vis[it])
        {
            dfs(it, adj, vis, dfsList);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    int start;
    cin >> start;
    vector<int> adj[n + 1];
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vis(n + 1, 0);
    vis[start] = 1;

    vector<int> dfsList;
    dfs(start, adj, vis, dfsList);
    cout << "Dfs: ";
    for (auto it : dfsList)
    {
        cout << it << " ";
    }
    return 0;
}