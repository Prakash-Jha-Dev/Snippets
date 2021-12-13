/// Name: EulerTour
/// Description: Maps a tree to an array to simplify subtree query
/// Detail: Tree, Subtree Queries
/// Guarantee: } // EulerTour

vector< vector<int> >adj;
/**
 * in : stores in time to a subtree root at in[x]
 * out : stores index of last_element at subtree rooted at x
 * rev_time : tells node's name in tree when timer was x 
 * i.e rev_time[i] = y means at time i, dfs visited node y for first time
 */
vector< int >in, out, rev_time;
void dfs(int to, int& timer)
{
    in[to] = ++timer;
    rev_time[timer] = to;
    for(auto x: adj[to])
    {
        // x is yet to be visited
        if(!in[x]) dfs(x, timer);
    }
    out[to] = timer;
}

// assign an ordering of vertex such that each subtree has a continuos index in mapped array
// gives index in [1,n]
// can be changed to assign index in [0,n-1]
void euler_tour(int root)
{
    in.assign(adj.size(),0);
    out.assign(adj.size(),0);
    rev_time.assign(adj.size(),0);

    int timer = 0;
    dfs(root, timer);
} // EulerTour