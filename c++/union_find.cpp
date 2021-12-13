/// Name: UnionFind
/// Description: Union find data structure with path compression and union by size 
/// Detail: Data Structure, DSU
/// Guarantee: } // UnionFind

vector<int> root, root_size;
void init_root(int n)
{
    root_size.assign(n + 1, 1);
    root.resize(n + 1);
    for (int i = 1; i <= n; i++)
        root[i] = i;
}

int get_root(int x)
{
    return (root[x] == x) ? x : root[x] = get_root(root[x]);
}

void combine_root(int x, int y)
{
    int u = get_root(x);
    int v = get_root(y);
    if (u != v)
    {
        if (root_size[u] > root_size[v])
        {
            root[v] = u;
            root_size[u] += root_size[v];
        }
        else
        {
            root[u] = v;
            root_size[v] += root_size[u];
        }
    }
} // UnionFind