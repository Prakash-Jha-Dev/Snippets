/// Name: Dijkstra
/// Description: Computes shortest path from single source to all vertex (only for non-negative edge weight)
/// Detail: Graph, Shortest Path
/// Guarantee: } // Dijkstra

int dijkstra(int src, int dest, int n, vector<list<pair<int, int>>> &adj)
{
    vector<int> dist(n + 1, 1000000);
    vector<bool> vis(n + 1, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {
        int ver = pq.top().second;
        int wt = pq.top().first;
        pq.pop();
        // skip shorter edges with heavier overall cost
        if (vis[ver])
            continue;
        vis[ver] = 1;
        for (auto x : adj[ver])
        {
            // relax the vertexes
            if ((wt + x.first) < dist[x.second])
            {
                dist[x.second] = wt + x.first;
                pq.push({dist[x.second], x.second});
            }
        }
    }
} // Dijkstra