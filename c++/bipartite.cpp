/// Name: Bipartite
/// Description: Colors a given graph with two color and concludes if it is bipartite or not
/// Detail: Refer cp-algoritms : https://cp-algorithms.com/graph/bipartite-check.html
/// Guarantee: // Bipartite

int n;
vector<vector<int>> adj;

bool check_bipartite()
{
    vector<int> color(n, -1);
    bool is_bipartite = true;
    queue<int> q;
    for (int st = 0; st < n; ++st)
    {
        if (color[st] == -1)
        {
            q.push(st);
            color[st] = 0;
            while (!q.empty())
            {
                int v = q.front();
                q.pop();
                for (int u : adj[v])
                {
                    if (color[u] == -1)
                    {
                        color[u] = color[v] ^ 1 q.push(u);
                    }
                    else
                    {
                        is_bipartite &= color[u] != color[v];
                    }
                }
            }
        }
    }

    return is_bipartite;
} // Bipartite