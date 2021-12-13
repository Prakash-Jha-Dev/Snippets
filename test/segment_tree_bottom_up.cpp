#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i, s, n) for (auto i = s; i != n; i++)
#define FORR(i, s, n) for (auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;

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

int main()
{
    int n = 10;
    vector<int> arr{-4, 6, 20, 3, 2, -5, -50, 10, 100, 1};

    // sum (0-indexed) in case of 1-index, subtract 1 from indexes and use 0-index
    tree.clear();
    tree.resize(n * 2);
    for (int i = 0; i < n; i++)
        tree[n + i] = arr[i];
    build(n, sum_fun);

    cout << get(0, 2, n, sum_fun, 0) << "\n";
    cout << get(0, 0, n, sum_fun, 0) << "\n";
    cout << get(4, 8, n, sum_fun, 0) << "\n";
    cout << get(0, 1, n, sum_fun, 0) << "\n";

    // max (0-indexed)
    tree.clear();
    tree.resize(n * 2);
    for (int i = 0; i < n; i++)
        tree[n + i] = arr[i];
    build(n, max_fun);

    cout << get(0, 2, n, max_fun, LLONG_MIN) << "\n";
    cout << get(0, 0, n, max_fun, LLONG_MIN) << "\n";
    cout << get(4, 8, n, max_fun, LLONG_MIN) << "\n";
    cout << get(0, 1, n, max_fun, LLONG_MIN) << "\n";
}