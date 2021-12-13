/// Name: CentroidDecomposition
/// Description: Finds the parent of all vertices in centroid decomposed tree
/// Detail: Graph, Centroid, Graph decomposition
/// Guarantee: CentroidDecomposition

void getCentroid(int& centroid, int idx, int subtreeSize, vector< vector< int > >&tree, vector< bool >&visited, vector< bool >&isCentroid, vector< int >&subtree)
{
    visited[idx] = true;
    for(auto x: tree[idx])
    {
        if(!visited[x] && !isCentroid[x])
        {
            if(subtree[x] > (subtreeSize/2))
            {
                getCentroid(centroid, x, subtreeSize, tree, visited, isCentroid, subtree);
                visited[idx] = false;
                return;
            }
        }
    }
    centroid = idx;
    visited[idx] = false;
}

void dfs(int idx, vector< vector< int > >&tree, vector< bool >&visited, vector< bool >&isCentroid, vector< int >&subtree)
{
    visited[idx] = true;
    subtree[idx] = 1;
    for(auto x: tree[idx])
    {
        if(!visited[x] && !isCentroid[x])
        {
            dfs(x, tree, visited, isCentroid, subtree);
            subtree[idx] += subtree[x];
        }
    }
    visited[idx] = false;
}

void decomposeTree(int par, int idx, vector< vector< int > >&tree, vector< int >&decomposedTree, vector< bool >&visited, vector< bool >&isCentroid, vector< int >&subtree)
{
    dfs(idx, tree, visited, isCentroid, subtree);
    int subtreeSize = subtree[idx];
    int centroid = idx;
    getCentroid(centroid, idx, subtreeSize, tree, visited, isCentroid, subtree);
    decomposedTree[centroid] = par;
    isCentroid[centroid] = true;
    for(auto x: tree[centroid])
    {
        if(!isCentroid[x])
        {
            decomposeTree(centroid, x, tree, decomposedTree, visited, isCentroid, subtree);
        }
    } 
}

vector< int >centroidDecomposition(vector< vector< int > >& tree)
{
    vector< int >decomposedTree(tree.size());
    vector< bool >visited(tree.size(),false);
    vector< bool >isCentroid(tree.size(), false);
    vector< int >subtree(tree.size(), 0);
    decomposeTree(-1, 0, tree, decomposedTree, visited, isCentroid, subtree);
    return decomposedTree;
} // CentroidDecomposition