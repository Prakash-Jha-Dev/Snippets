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
unordered_map<int, int> comp, vis, assignment;
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

bool SAT()
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
    for (int i = (int)ord.size() - 1, j = 0; i >= 0; i--)
    {
        if (!comp[ord[i]])
        {
            dfs(ord[i], adjt, ++j);
        }
    }
    for (auto x : comp)
    {
        if (comp[x.first] == comp[-x.first])
            return 0;
        // component having higher index is towards right (x=>y) by topoligical sorting
        // and hence should have true value
        assignment[x.first] = comp[x.first] > comp[-x.first];
    }
    return 1;
} // 2 SAT


int main()
{
    // n variables and m clauses
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[-u].push_back(v);
        adj[-v].push_back(u);
        if(adj.find(u) == adj.end()) adj[u] = {};
        if(adj.find(v) == adj.end()) adj[v] = {};

        adjt[v].push_back(-u);
        adjt[u].push_back(-v);
        if(adjt.find(-u) == adjt.end()) adjt[-u] = {};
        if(adjt.find(-v) == adjt.end()) adjt[-v] = {};
    }

    cout << "Valid assignment exist : " << SAT() << "\n";
    for (auto x : assignment)
        if (x.first > 0)
            cout << x.first << " " << x.second << "\n";
}