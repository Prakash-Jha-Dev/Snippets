/// Name: Kruskal
/// Description: Minimum spanning tree algorithm
/// Detail: Graph, Minimum Spanning Tree
/// Guarantee: } // Kruskal
/// Dependencies: union_find

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
} // Kruskal