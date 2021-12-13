/// Name: Articulation Points and Bridges
/// Description: Finds cut vertices and briges in a graph
/// Detail: DFS, Bridge, Articulation Point, Graph
/// Guarantee: } // cutPointsandBridges

vector< int >low;
vector< int >disc;
vector< vector< int > >adj;
int timer = 0;

vector< int >articulationPoint;
vector< pair<int,int> >bridges;
void dfs(int curr, int par = -1)
{
    low[curr] = disc[curr] = ++timer;
    int child = 0;
    for(int x: adj[curr])
    {
        if(x == par) continue;
        if(!disc[x])
        {
            child++;
            dfs(x, curr);
            low[curr] = min(low[curr], low[x]);
            // for cut points
            if(low[x] >= disc[curr] && par != -1) articulationPoint.push_back(curr);
            // for bridges
            if(low[x] > disc[curr]) bridges.push_back({min(curr,x), max(curr,x)});
        }
        else low[curr] = min(low[curr], disc[x]);
    }
    if(par == -1 && child > 1) articulationPoint.push_back(curr);
}

void cutPointsandBridges(int n)
{
    timer = 0;
    low.assign(n,0);
    disc.assign(n,0);
    for(int i=0; i<n; i++) if(!disc[i]) dfs(i);
} // cutPointsandBridges
