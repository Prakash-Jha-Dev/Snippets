/// Name: BellmanFord
/// Description: Computes shortest path from single source to all vertex (even with negative edge weight)
/// Detail: Graph, Shortest Path
/// Guarantee: } // BellmanFord

void bellmanFord(int src, vector< vector < pair<int,int> > >& adj)
{
    // adjust max cost, default to 1000
    vector< int >cost(adj.size(), 1000), par(adj.size(), 0);
    cost[src] = 0;
    bool negativeCycle = false;
    // no.of levels: n-1,to find shortest path and nth to detect negative loop
    for(int i=1; i<adj.size(); i++)
    {
        //local relaxtion from jth vertice
        for(int j=1; j<adj.size(); j++)
        {
            // relax all connecting nodes with updated weight
            for(auto x: adj[j])
            {
                if(cost[x.second] > cost[j] + x.first)
                {
                    cost[x.second] = cost[j] + x.first;
                    par[x.second] = j;
                    // if weight updates in nth iteration then there must be some negative cycle 
                    // associated with jth vertice
                    if(i == adj.size()-1 ) negativeCycle = true;
                }
            }
        }
    }
    if(negativeCycle) cout<<"negative cycle detected\n";
    else
    {
        for(int i=1; i<cost.size(); i++) cout<<cost[i]<<" "; 
    }
} // BellmanFord
