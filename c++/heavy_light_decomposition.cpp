/// Name: HeavyLightDecomposition
/// Description: Decomposes a tree into set of continuous paths and implements segment tree on it
/// Detail: HLD, Tree, Path Queries with Updates
/// Guarantee: } // HeavyLightDecomposition

// structure of node in arr
typedef struct A_node
{
    int vert_val;
    int edge_val;
    bool lazy_edge_rem;
    bool lazy_vert_rem;
    int lazy_edge_val;
    int lazy_vert_val;

    friend ostream &operator<<(ostream &out, A_node &x)
    {
        out << "Value (vertex) : " << x.vert_val << "\n";
        out << "Value (edge) : " << x.edge_val << "\n";
        out << "Is pending Vertex Update to child : " << x.lazy_vert_rem << "\n";
        out << "Is pending Edge Update to child : " << x.lazy_edge_rem << "\n";
        out << "Pending Vertex Value : " << x.lazy_vert_val << "\n";
        out << "Pending Edge Value : " << x.lazy_edge_val << "\n";
        cout << "\n";
    }
} anode;

// structure for mapping node from tree to arr
typedef struct H_node
{
    int idx_arr;
    int chain_head;
    int heavy_child;
    int heavy_edge_cost;
    int light_edge_cost;
    int depth;
    int par;
    int in;
    int out;
    int subtree_size; //same as out - in

    friend ostream &operator<<(ostream &out, H_node &x)
    {
        out << "Index in array : " << x.idx_arr << "\n";
        out << "Head of Chain : " << x.chain_head << "\n";
        out << "Depth from root : " << x.depth << "\n";
        out << "Parent : " << x.par << "\n";
        out << "Heaviest child : " << x.heavy_child << "\n";
        out << "Cost of incoming heavy edge (if any) : " << x.heavy_edge_cost << "\n";
        out << "Cost of incoming light edge (if any) : " << x.light_edge_cost << "\n";
        out << "Starting index of subtree : " << x.in << "\n";
        out << "Ending index of subtree : " << x.out << "\n";
        out << "Size of subtree : " << x.subtree_size << "\n";
        cout << "\n";
    }
} hnode;

vector<vector<int>> par;            // to store parents in jumps of 2^x : Used for lca
vector<int> val;                    // to store values at vertex
vector<vector<pair<int, int>>> adj; // to store tree {edge_cost,opp_vertex}
vector<hnode> tree;                 // to store mapping info from tree to arr
vector<anode> arr;                  // arr to be used as segment tree
vector<int> look;                   // to get index in tree of known index in array i.e reverse mapping from arr to tree
int pos = 1;                        // NOTE: start index in segment_tree (keep same as starting index of adj i.e 0 or 1). At end, it stores the last index
// NOTE: keep the same value as initial value of pos i.e. 0 or 1 which is same as starting index of adj
int start_index = pos;

int dfs(int to, int from)
{
    tree[to].depth = tree[from].depth + 1;
    tree[to].heavy_child = -1;
    tree[to].par = from;
    tree[to].subtree_size = 1;
    int max_child_size = 0;
    int heavy_edge_cost = 0;
    for (auto x : adj[to])
    {
        if (x.second != from)
        {
            int c_size = dfs(x.second, to);
            tree[to].subtree_size += c_size;
            if (c_size > max_child_size)
            {
                tree[to].heavy_child = x.second;
                heavy_edge_cost = x.first;
                max_child_size = c_size;
            }
        }
    }
    if (tree[to].heavy_child != -1)
    {
        tree[tree[to].heavy_child].heavy_edge_cost = heavy_edge_cost;
        tree[tree[to].heavy_child].light_edge_cost = 0;
    }
    return tree[to].subtree_size;
}

void decompose(int i, int head)
{
    if (i != head)
        tree[i].light_edge_cost = 0;
    tree[i].chain_head = head;
    look[pos] = i;
    tree[i].idx_arr = pos++;
    tree[i].in = tree[i].idx_arr;
    if (tree[i].heavy_child != -1)
        decompose(tree[i].heavy_child, head);
    for (auto x : adj[i])
    {
        if (x.second != tree[i].par && x.second != tree[i].heavy_child)
        {
            tree[x.second].heavy_edge_cost = 0;
            tree[x.second].light_edge_cost = x.first;
            decompose(x.second, x.second);
        }
    }
    tree[i].out = pos - 1;
}

// decomposes actual tree into many paths i.e. continuous segment in arr
// each node stores info about its position in array (.idx_arr)
// it's depth from root (.depth), it's parent (.par) and the heavy child (.heavy_child)
// the head of chain it is in (.head)
// the start index in array of subtree (.in) and last index of it's subtree (.out)
// the edge (.light_edge_cost is from heavy_chain to another heavy chain ) and (.heavy_edge_cost is to next vertice in same chain)
void hld(int root)
{
    tree[root].depth = 0;
    tree[root].light_edge_cost = 0;
    tree[root].heavy_edge_cost = 0;
    dfs(root, root);
    decompose(root, root);
}

// to build a segment tree with values of vertices and edges of the tree as per mapping by hld
void build(int idx, int st, int ed)
{
    if (st == ed)
    {
        // look[i] stores index in tree having index i in arr
        // fill vertex and edge values
        arr[idx].vert_val = val[look[st]];
        // heavy_edge_cost or light_edge_cost : one is zero and other might not be
        arr[idx].edge_val = tree[look[st]].heavy_edge_cost + tree[look[st]].light_edge_cost;
        arr[idx].lazy_vert_rem = false;
        arr[idx].lazy_edge_rem = false;
        return;
    }
    int mid = (st + ed) >> 1;
    build(idx << 1, st, mid);
    build(idx << 1 | 1, mid + 1, ed);

    // seg tree to give sum of values on edges and max val on path
    arr[idx].vert_val = arr[idx << 1].vert_val + arr[idx << 1 | 1].vert_val;
    arr[idx].edge_val = max(arr[idx << 1].edge_val, arr[idx << 1 | 1].edge_val);
    arr[idx].lazy_edge_rem = false;
    arr[idx].lazy_vert_rem = false;
}

// to push updates to child before accessing them
void propogate_lazy(int idx, int st, int ed)
{
    // if not leaf, push the updates
    if (st != ed)
    {
        // if vertex values are pending to be pushed to childs
        if (arr[idx].lazy_vert_rem)
        {
            int mid = (st + ed) >> 1;
            // since all child the value x, sum becomes x*n
            arr[idx << 1].vert_val = arr[idx].lazy_vert_val * (mid - st + 1);
            arr[idx << 1].lazy_vert_rem = true;

            arr[idx << 1 | 1].vert_val = arr[idx].lazy_vert_val * (ed - mid);
            arr[idx << 1 | 1].lazy_vert_rem = true;

            arr[idx].lazy_vert_rem = false;
        }

        // if edge values are pending to be pushed to childs
        if (arr[idx].lazy_edge_rem)
        {
            int mid = (st + ed) >> 1;
            // since all child have same values, max value is same
            arr[idx << 1].edge_val = arr[idx].lazy_edge_val;
            arr[idx << 1].lazy_edge_rem = true;

            arr[idx << 1 | 1].edge_val = arr[idx].lazy_edge_val;
            arr[idx << 1 | 1].lazy_edge_rem = true;

            arr[idx].lazy_edge_rem = false;
        }
    }
    else
    {
        arr[idx].lazy_edge_rem = false;
        arr[idx].lazy_vert_rem = false;
    }
}

// to query segment in range [l...r]
// for given tree, sum of values of vertices lying in range
int query_vert(int idx, int st, int ed, int l, int r)
{
    // if current section lies completely in range, return the value directly
    if (l <= st && ed <= r)
        return arr[idx].vert_val;
    propogate_lazy(idx, st, ed);
    int mid = (st + ed) >> 1;
    if (mid >= r)
        return query_vert(idx << 1, st, mid, l, r);
    if (mid < l)
        return query_vert(idx << 1 | 1, mid + 1, ed, l, r);
    return query_vert(idx << 1, st, mid, l, mid) + query_vert(idx << 1 | 1, mid + 1, ed, mid + 1, r);
}

// to query segment in range [l...r]
// for given tree, max of values of edges lying in range
int query_edge(int idx, int st, int ed, int l, int r)
{
    // if current section lies completely in range, return the value directly
    if (l <= st && ed <= r)
        return arr[idx].edge_val;
    propogate_lazy(idx, st, ed);
    int mid = (st + ed) >> 1;
    if (mid >= r)
        return query_edge(idx << 1, st, mid, l, r);
    if (mid < l)
        return query_edge(idx << 1 | 1, mid + 1, ed, l, r);
    return max(query_edge(idx << 1, st, mid, l, mid), query_edge(idx << 1 | 1, mid + 1, ed, mid + 1, r));
}

// to update the value of vertexes in range [l...r]
void update_vert(int idx, int st, int ed, int l, int r, int val)
{
    // placing it before new update, in case updates cannot be merged (often they can be merged tho.)
    propogate_lazy(idx, st, ed);
    if (l <= st && ed <= r)
    {
        arr[idx].vert_val = val * (r - l + 1);
        arr[idx].lazy_vert_rem = true;
        arr[idx].lazy_vert_val = val;
        return;
    }
    int mid = (st + ed) >> 1;
    if (mid >= r)
        update_vert(idx << 1, st, mid, l, r, val);
    else if (mid < l)
        update_vert(idx << 1 | 1, mid + 1, ed, l, r, val);
    else
    {
        update_vert(idx << 1, st, mid, l, mid, val);
        update_vert(idx << 1 | 1, mid + 1, ed, mid + 1, r, val);
    }
    arr[idx].vert_val = arr[idx << 1].vert_val + arr[idx << 1 | 1].vert_val;
}

// to update the value of edges in range [l...r]
void update_edge(int idx, int st, int ed, int l, int r, int val)
{
    // placing it before new update, in case updates cannot be merged (often they can be merged tho.)
    propogate_lazy(idx, st, ed);
    if (l <= st && ed <= r)
    {
        arr[idx].edge_val = val;
        arr[idx].lazy_edge_rem = true;
        arr[idx].lazy_edge_val = val;
        return;
    }
    int mid = (st + ed) >> 1;
    if (mid >= r)
        update_edge(idx << 1, st, mid, l, r, val);
    else if (mid < l)
        update_edge(idx << 1 | 1, mid + 1, ed, l, r, val);
    else
    {
        update_edge(idx << 1, st, mid, l, mid, val);
        update_edge(idx << 1 | 1, mid + 1, ed, mid + 1, r, val);
    }
    arr[idx].edge_val = max(arr[idx << 1].edge_val, arr[idx << 1 | 1].vert_val);
}

// LCA
void createLcaTable(int root)
{
    par.clear();
    par.resize(adj.size());
    int sz = log2(par.size()) + 2;
    for (int i = 0; i < par.size(); i++)
        par[i].resize(sz);
    for (int i = start_index; i < adj.size(); i++)
        par[i][0] = tree[i].par;

    for (int i = 1; i < sz; i++)
    {
        for (int j = 0; j < par.size(); j++)
        {
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }
}

int lca(int u, int v)
{
    if (tree[u].depth < tree[v].depth)
        swap(u, v);

    int diff = (tree[u].depth - tree[v].depth);
    for (int i = par[u].size() - 1; i >= 0; i--)
    {
        if (diff & (1 << i))
        {
            u = par[u][i];
        }
    }
    if (u == v)
        return u;

    for (int i = par[u].size() - 1; i >= 0; i--)
    {
        if (par[u][i] != par[v][i])
        {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

int dist(int u, int v)
{
    return tree[u].depth + tree[v].depth - 2 * tree[lca(u, v)].depth;
}

// function to get value of vertices along path from u to v
// here we're finding sum of all vertice
int query_tree_vert(int u, int v)
{
    int l = lca(u, v);
    int ans = 0;
    // get answer for path from u to l
    while (tree[u].chain_head != tree[l].chain_head)
    {
        ans += query_vert(1, start_index, pos, tree[tree[u].chain_head].idx_arr, tree[u].idx_arr);
        u = tree[tree[u].chain_head].par;
    }
    ans += query_vert(1, start_index, pos, tree[l].idx_arr, tree[u].idx_arr);

    // get answer for path from v to l (excluding l)
    while (tree[v].chain_head != tree[l].chain_head)
    {
        ans += query_vert(1, start_index, pos, tree[tree[v].chain_head].idx_arr, tree[v].idx_arr);
        v = tree[tree[v].chain_head].par;
    }
    if (v != l)
    {
        // v and l are on same chain and we need to exclude l
        l = tree[l].heavy_child;
        if (l > -1 && tree[l].idx_arr <= tree[v].idx_arr)
        {
            ans += query_vert(1, start_index, pos, tree[l].idx_arr, tree[v].idx_arr);
        }
    }

    return ans;
}

// function to get value of edges along path from u to v
// here we're finding max of all edges
int query_tree_edge(int u, int v)
{
    int l = lca(u, v);
    int ans = INT_MIN;
    // get answer for path from u to l
    while (tree[u].chain_head != tree[l].chain_head)
    {
        ans = max(ans, query_edge(1, start_index, pos, tree[tree[u].chain_head].idx_arr, tree[u].idx_arr));
        u = tree[tree[u].chain_head].par;
    }
    int temp_l = tree[l].heavy_child;
    if (temp_l > -1 && tree[temp_l].idx_arr <= tree[u].idx_arr)
    {
        ans = max(ans, query_edge(1, start_index, pos, tree[temp_l].idx_arr, tree[u].idx_arr));
    }

    // get answer for path from v to l
    while (tree[v].chain_head != tree[l].chain_head)
    {
        ans = max(ans,query_edge(1, start_index, pos, tree[tree[v].chain_head].idx_arr, tree[v].idx_arr));
        v = tree[tree[v].chain_head].par;
    }
    if (temp_l > -1 && tree[temp_l].idx_arr <= tree[v].idx_arr)
    {
        ans = max(ans, query_edge(1, start_index, pos, tree[temp_l].idx_arr, tree[v].idx_arr));
    }

    return ans;
}

// function to update value of vertices along path from u to v
// here we're storing sum of vertice in inner nodes
void update_tree_vert(int u, int v, int val)
{
    int l = lca(u, v);
    int ans = 0;
    // update vertices along path from u to l
    while (tree[u].chain_head != tree[l].chain_head)
    {
        update_vert(1, start_index, pos, tree[tree[u].chain_head].idx_arr, tree[u].idx_arr, val);
        u = tree[tree[u].chain_head].par;
    }
    update_vert(1, start_index, pos, tree[l].idx_arr, tree[u].idx_arr, val);

    // update vertices along path from v to l (excluding l)
    while (tree[v].chain_head != tree[l].chain_head)
    {
        update_vert(1, start_index, pos, tree[tree[v].chain_head].idx_arr, tree[v].idx_arr, val);
        v = tree[tree[v].chain_head].par;
    }
    if (v != l)
    {
        // v and l are on same chain and we need to exclude l
        l = tree[l].heavy_child;
        if (l > -1 && tree[l].idx_arr <= tree[v].idx_arr)
            update_vert(1, start_index, pos, tree[l].idx_arr, tree[v].idx_arr, val);
    }
}

// function to update value of edges along path from u to v
// here we're storing max of edge in inner nodes
void update_tree_edge(int u, int v, int val)
{
    int l = lca(u, v);
    int ans = 0;
    // update edges along path from u to l
    while (tree[u].chain_head != tree[l].chain_head)
    {
        update_edge(1, start_index, pos, tree[tree[u].chain_head].idx_arr, tree[u].idx_arr, val);
        u = tree[tree[u].chain_head].par;
    }
    int temp_l = tree[l].heavy_child;
    if (temp_l > -1 && tree[temp_l].idx_arr <= tree[u].idx_arr)
        update_edge(1, start_index, pos, tree[temp_l].idx_arr, tree[u].idx_arr, val);

    // update edges along path from v to l
    while (tree[v].chain_head != tree[l].chain_head)
    {
        update_edge(1, start_index, pos, tree[tree[v].chain_head].idx_arr, tree[v].idx_arr, val);
        v = tree[tree[v].chain_head].par;
    }
    if (temp_l > -1 && tree[temp_l].idx_arr <= tree[v].idx_arr)
        update_edge(1, start_index, pos, tree[temp_l].idx_arr, tree[v].idx_arr, val);
}

void init(int root)
{
    tree.clear();
    tree.resize(adj.size());
    look.clear();
    look.resize(adj.size());
    hld(root);
    // subtract one from pos, so that it stores the last index allocated
    pos--;
    createLcaTable(root);
    arr.clear();
    arr.resize(4 * pos);
    build(1, start_index, pos);
}

int input_tree(vector<vector<pair<int, int>>> &adj)
{
    // input number of vertices
    int n, u, v, w;
    cin >> n;

    adj.clear();
    adj.resize(n + 1);
    for (int i = 1; i < n; i++)
    {
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    // input the value on each vertice
    val.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> val[i];

    return n;
} // HeavyLightDecomposition