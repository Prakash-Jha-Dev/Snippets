#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i, s, n) for (auto i = s; i != n; i++)
#define FORR(i, s, n) for (auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;


unordered_map<int, vector<int>> adj, adjt;
unordered_map<int, int> comp, vis;
vector<vector<int>> scc;
vector<int> ord;

void dfs(int i, unordered_map<int, vector<int>> &adj, int type)
{
    vis[i] = 1;
    for (int x : adj[i])
    {
        if (!vis[x])
            dfs(x, adj, type);
    }
    if (type == 0)
        ord.push_back(i);
    else
        comp[i] = type;
}

void SCC()
{
    ord.clear();
    vis.clear();
    comp.clear();

    for (auto &x : adj)
    {
        if (!vis[x.first])
        {
            dfs(x.first, adj, 0);
        }
    }

    vis.clear();
    int j = 0;
    for (int i = (int)ord.size() - 1; i >= 0; i--)
    {
        if (!comp[ord[i]])
        {
            dfs(ord[i], adjt, ++j);
        }
    }

    // comp stores the scc index of given node
    scc.clear();
    scc.resize(j + 1);
    for (auto &x : comp)
    {
        scc[x.second].push_back(x.first);
    }

} // StronglyConnectedComponent






int main()
{
    // n variables and m edges
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);

        adjt[v].push_back(u);
    }

    SCC();
    for(auto& nodes : scc)
    {
        for(auto& node : nodes) cout<<node<<" "; cout<<"\n";
    }
}