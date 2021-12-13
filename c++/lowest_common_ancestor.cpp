/// Name: LowestCommonAncestor
/// Description: Lookup table based implementation to find lca of two nodes
/// Detail: Graph, LCA, Tree
/// Guarantee: LowestCommonAncestor

void dfs(int from, int to, vector<int>& level, vector< vector<int> >& par, vector< vector<int> >& tree)
{
    par[to][0] = from;
    level[to] = level[from] + 1;
    for(auto x: tree[to])
    {
        if(x != from)
        {
            dfs(to, x, level, par, tree);
        }
    }
}

vector< vector<int> >lcaTable(int root, vector< vector<int> >tree, vector<int>& level)
{
    vector< vector<int> >par(tree.size());
    level.resize(tree.size());

    int sz = log2(par.size())+2;
    for(int i=0; i<par.size(); i++) par[i].resize(sz);

    level[root] = 0;
    dfs(root, root, level, par, tree);

    for(int i=1; i<sz; i++)
    {
        for(int j=0; j<par.size(); j++)
        {
            par[j][i] = par[par[j][i-1]][i-1];
        }
    }
    return par;
}

int lca(int u, int v, vector< int >& level, vector< vector<int> >& table)
{
    if(level[u] < level[v])
    {
        swap(u, v);
    }
    int diff = (level[u] - level[v]);
    for(int i=table[u].size()-1; i>=0; i--)
    {
        if(diff&(1<<i))
        {
            u = table[u][i];
        }
    }
    if(u == v) return u;

    for(int i=table[u].size()-1; i>=0; i--)
    {
        if(table[u][i] != table[v][i])
        {
            u = table[u][i];
            v = table[v][i];
        }
    }
    return table[u][0];
}

int dist(int u, int v, vector< int >& level, vector< vector<int> >& table)
{
    return level[u] + level[v] - 2*level[lca(u,v,level,table)];
} // LowestCommonAncestor