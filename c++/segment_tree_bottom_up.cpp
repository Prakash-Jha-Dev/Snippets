/// Name: SegmentTreeBottomUp
/// Description: Segment Tree implementation using bottom-up technique
/// Detail: Segment tree, Data Structure, Range Query
/// Guarantee: } // SegmentTreeBottomUp

auto sum_fun = [](const auto x, const auto y) { return (x + y); };
auto max_fun = [](const auto x, const auto y) { return (x) > (y) ? (x) : (y); };
auto min_fun = [](const auto x, const auto y) { return (x) < (y) ? (x) : (y); };

vector<long long> tree(2 * (1e5 + 1));

void build(int n, auto &fun)
{
    for (int i = n - 1; i > 0; --i)
    {
        tree[i] = fun(tree[i << 1], tree[i << 1 | 1]);
    }
}

void update(int pos, long long val, int n, auto &fun)
{
    pos += n;
    for (tree[pos] = val; pos > 1; pos >>= 1)
    {
        tree[pos >> 1] = fun(tree[pos], tree[pos ^ 1]);
    }
}

// range is [l,r]
long long get(int l, int r, int n, auto &fun, auto init = 0LL)
{
    long long ans = init;
    for (l += n, r = r + n + 1; l < r; l >>= 1, r >>= 1)
    {
        if (l & 1)
            ans = fun(ans, tree[l++]);
        if (r & 1)
            ans = fun(ans, tree[--r]);
    }
    return ans;
} // SegmentTreeBottomUp