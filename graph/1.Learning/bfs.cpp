#include <bits/stdc++.h>
using namespace std;

void bfs(int start, vector<int> adj[], vector<int> &vis, vector<int> &bfslist, queue<int> &q)
{
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        bfslist.push_back(node);
        for (auto it : adj[node])
        {
            if (!vis[it])
            {
                vis[it] = 1;
                q.push(it);
            }
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
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> vis(n + 1, 0);
    vector<int> bfslist;
    queue<int> q;

    vis[start] = 1;
    q.push(start);

    bfs(start, adj, vis, bfslist, q);
    cout<< "Bfs: ";
    for (auto it : bfslist)
    {
        cout << it << " ";
    }

    return 0;
}