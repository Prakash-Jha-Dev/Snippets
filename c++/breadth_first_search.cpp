/// Name: BFS
/// Description: Breadth first search implementation
/// Detail: BFS, Graph, Tree
/// Guarantee: } // BFS

void bfs(int start, int n, vector< vector< int > >&adj)
{
    vector< int >dist(n+1);
    vector< bool >vis(n+1);

    queue< vector< int > >q;
    q.push({start,0});
    while(q.size())
    {
        auto p = q.front();
        q.pop();

        if(vis[p[0]]) continue;
        vis[p[0]] = 1;
        dist[p[0]] = p[1];

        for(auto x: adj[p[0]])
        {
            if(!vis[x]) q.push({x,p[1]+1});
        }
    }
} // BFS