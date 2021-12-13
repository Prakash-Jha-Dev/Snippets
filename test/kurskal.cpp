#include <bits/stdc++.h>
using namespace std;


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



int kruskal(vector< vector<int> >& edge, int n)
{
    stable_sort(edge.begin(),edge.end());
    init_root(n);
    int cost = 0;
    for(auto x: edge)
    {
        if(get_root(x[1]) != get_root(x[2]))
        {
            cost += x[0];
            combine_root(x[1], x[2]);
        }
    }
    return cost;
}

int main()
{
    int n,m;
    cin>>n>>m;

    vector< vector<int> >edge;
    for(int i=1; i<=m; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        edge.push_back({w,v,u});
    }

    cout<<kruskal(edge, n);
}
