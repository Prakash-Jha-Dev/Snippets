/// Name: FlyodWarshall
/// Description: Computes shortest path from between all vertexes (even with negative edge weight)
/// Detail: Graph, Shortest Path
/// Guarantee: } // FlyodWarshall

void flyodWarshall(vector< vector < int > >& adj)
{
    int n = adj.size() - 1;
    //path[x][y] storoes info path from x....k and k...y. 
    //i.e path[x][y] = path[x][path[x][y]] and path[path[x][y]][y]
    //base case is path[x][y] = x means x-y is directly connected via edge xy
    vector< vector< int > >path(n+1, vector<int>(n+1));
    for(int i=1; i<=n; i++) adj[i][i] = 0, path[i][i] = i;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(adj[i][j] != INF) path[i][j] = i;

    for(int k=1; k<=n; k++)
    {
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(adj[i][k]!=INF && adj[k][j]!=INF)
                if(adj[i][j] > adj[i][k] + adj[k][j])
                {
                    adj[i][j] = adj[i][k] + adj[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
    bool negativeCycle = false;
    for(int i=1; i<=n; i++) if(adj[i][i] < 0) negativeCycle = true;
    if(negativeCycle) cout<<"negative cycle detected\n";
} // FlyodWarshall