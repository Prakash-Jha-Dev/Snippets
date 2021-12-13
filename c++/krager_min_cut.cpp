/// Name: KragerMinCut
/// Description: Randomized algo to partition a graph into 2 sets and compute min number of edges between partition
/// Detail: Graph, Min Cut, Randomization, Probabilistic Algo, Edge Compression
/// Guarantee: } // KragerMinCut

void printAdj(vector< multiset<int> > &adj, int n)
{
	for(int i=1; i<=n; i++)
	{
		cout<<i<<" :: ";
		for(int j:adj[i]) cout<<j<<" "; cout<<"\n";
	}
	cout<<"\n";
}

/**
 *  Krager Min Cut
 *  randomly selects an edge and combines the vertices into 1 until only one edge is left
 *  at end, the only left edge is between two paritions represented by vertices on either side
 *  input graph can have multiple edges, self loop
 * 
 *  returns min cut with probability 2/(n*(n-1)), so repeat it same number of times
 * 
 *  Computing min cut using flow takes nC2 iterations for choice of s and t and O(n^3) per iteration
 *  The following algorithm is n^2logn per iteration and often gives correct result in O(n) iteration**
 */
int kargerMinCut(vector< multiset<int> >adj)
{
	int n = adj.size() - 1;
	// printAdj(adj, n);
    // div stores matching vertex set, e.g. div[x] = y means x and y are in same set
    // div stores union without compression
	vector< int >vert, pos(n+1), div(n+1);
    // vert and pos is used to select a vertex randomly and then an edge to compress at each stage
	for(int i=1; i<=n; i++) vert.push_back(i), pos[i] = i-1, div[i] = i;
	int u,v;

	// iterates n times, inner loop complexity is n log n (due to add n element in set from another set)
	while(vert.size() > 2)
	{
		int tp = uniform_int_distribution<int>(0,vert.size()-1)(rng);
		pos[vert[tp]] = vert.size()-1;
		pos[vert.back()] = tp;
		swap(vert.back(), vert[tp]);
		u = vert.back();
		auto it = adj[u].begin();
		advance(it, uniform_int_distribution<int>(0,adj[u].size()-1)(rng));
		v = *it;

		if(adj[u].size() < adj[v].size()) swap(u, v);
        div[v] = div[u];
		// cout<<u<<" combines with "<<v<<"\n";
		adj[u].erase(v);
		adj[v].erase(u);

		for(auto x: adj[v])
		{
			int ct = adj[x].count(v);
			adj[x].erase(v);
			while(ct--) adj[x].insert(u),adj[u].insert(x);
		}
		// for(auto x: adj[v]) adj[u].insert(x);
		adj[v].clear();
		pos[vert.back()] = pos[v];
		swap(vert.back(),vert[pos[v]]);
		vert.pop_back();

		// printAdj(adj, n);
	}
	return adj[vert[0]].size();
} // KragerMinCut