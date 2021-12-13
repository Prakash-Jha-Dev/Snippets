#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> dist, par;
int max_dist, node;
void dfs(int to, int from)
{
    par[to] = from;
    dist[to] = dist[from] + 1;
    if (dist[to] > dist[node])
        node = to;

    for (auto x : adj[to])
    {
        if (x != from)
            dfs(x, to);
    }
}

vector<int> diameter(int n)
{
    par.resize(n + 1);
    dist.assign(n + 1, 0);
    node = 1;
    dfs(1, 0);
    int u = node;

    dist.assign(n + 1, 0);
    dfs(node, 0);
    int v = node;

    vector<int> path;
    while (v != u)
    {
        path.push_back(v);
        v = par[v];
    }
    path.push_back(u);

    return path;
} // DiameterOfTree

int main()
{
    int n;
    cin >> n;

    adj.clear();
    adj.resize(n + 1);

    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto d = diameter(n);
    for (auto x : d)
        cout << x << " ";
}

// Input
// 9
// 1 2
// 2 3
// 2 4
// 4 5
// 5 6
// 1 7
// 7 8
// 1 9