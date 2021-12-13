
/// Name: TopologicalOrder
/// Description: Finds an ordering of directed graph, ensuring dependencies gets resolved first
/// Detail: Data Structure, Graph, Topology, Dependency Graph, DAG
/// Guarantee: } // TopologicalOrder


vector<int>topological;

void dfs(int i, auto& vis, auto& adj)
{
	vis[i]=true;

	for(auto x:adj[i])
	{
		if(!vis[x])
		{
			dfs(x,vis,adj);
		}
	}
	topological.push_back(i);
}

void topological_sort(vector< list<int> >& adj)
{
	int n=adj.size();
	topological.reserve(n);
	vector<bool>vis(n,false);

	for(int i=1;i<n;i++)
	{
		if(!vis[i])
		{
			dfs(i,vis,adj);
		}
	}
} // TopologicalOrder