/// Name: DFS
/// Description: Depth first search implementation
/// Detail: DFS, Graph, Tree
/// Guarantee: } // DFS

vector< vector<int> >adj;
vector< int >dist;

void dfs_tree(int to, int from)
{
    dist[to] = dist[from] + 1;
    for(auto x: adj[to])
    {
        if(x != from)
        {
            dfs_tree(x, to);
        }
    }
}

void dfs_graph(int to, int from, vector<bool>& vis)
{
    vis[to] = 1;
    dist[to] = dist[from] + 1;
    for(auto x: adj[to])
    {
        if(!vis[x])
        {
            dfs_graph(x, to, vis);
        }
    }
} // DFS