/// Name: DiameterOfTree
/// Description: Computes one of the longest path in tree
/// Detail: Tree, Diameter
/// Guarantee: } // DiameterOfTree

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