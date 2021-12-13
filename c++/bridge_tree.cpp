/// Name: BridgeTree
/// Description: Compress cycle in graph and create graph(actually a tree) where each edge is a bridge
/// Detail: Graph compression, Tree, Bridge, Cacti graph, Find and detect cycle
/// Guarantee: } // BridgeTree

vector< int >low; // indexes having same low value are connceted like a cycle
vector< int >disc;
vector< vector< int > >adj; // original graph
vector< vector< int > >adjc; // compressed graph i.e. bridge tree i.e. cycles are compressed to single node 
int timer = 0;

void dfs(int curr, int par = -1)
{
    low[curr] = disc[curr] = ++timer;
    int child = 0;
    // compute the low(i.e. component number) of itself and all childrens
    for(int x: adj[curr])
    {
        if(x == par) continue;
        if(!disc[x])
        {
            child++;
            dfs(x, curr);
            low[curr] = min(low[curr], low[x]);
        }
        else low[curr] = min(low[curr], disc[x]);
    }
    // add edge in compressed graph with childrens not lying in same component
    for(int x: adj[curr])
    {
        if(x == par) continue;
        if(low[x] != low[curr])
        {
            adjc[curr].push_back(x);
            adjc[x].push_back(curr);
        }
    }
}

// 0-based index
void bridgeTree(int n)
{
    timer = 0;
    low.assign(n,0);
    disc.assign(n,0);
    adjc.clear();
    adjc.resize(n);
    for(int i=0; i<n; i++) if(!disc[i]) dfs(i);

} // BridgeTree