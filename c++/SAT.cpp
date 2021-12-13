/// Name: 2 SAT
/// Description: Boolean satisfiability problem for clauses with two component
/// Detail: SCC, Maths, Graph
/// Guarantee: } // 2 SAT

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
