/// Name: Prim
/// Description: Minimum spanning tree algorithm
/// Detail: Graph, Minimum Spanning Tree
/// Guarantee: } // Prim

int prim(vector<vector<pair<int, int>>> &adj, int n)
{
    int src = 1;
    set<pair<int, int>> data;
    vector<bool> vis(n + 1);
    int cost = 0;
    vis[src] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (auto z : adj[src])
            if (!vis[z.second])
                data.insert(z);
        pair<int, int> m = {0, src};
        while (vis[m.second])
        {
            m = *data.begin();
            data.erase(data.begin());
        }
        cost += m.first;
        src = m.second;
        // cout<<m.first<<" "<<m.second<<"\n";
        vis[src] = 1;
    }
    return cost;
} // prim