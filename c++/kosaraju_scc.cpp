/// Name: StronglyConnectedComponent
/// Description: Kosaraju Algorithm to find scc in graph
/// Detail: SCC, Maths, Graph
/// Guarantee: } // StronglyConnectedComponent


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