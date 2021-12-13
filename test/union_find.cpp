#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;

vector<int> root, root_size;
void init_root(int n)
{
    root_size.assign(n + 1, 1);
    root.resize(n + 1);
    for (int i = 1; i <= n; i++)
        root[i] = i;
}

int get_root(int x)
{
    return (root[x] == x) ? x : root[x] = get_root(root[x]);
}

void combine_root(int x, int y)
{
    int u = get_root(x);
    int v = get_root(y);
    if (u != v)
    {
        if (root_size[u] > root_size[v])
        {
            root[v] = u;
            root_size[u] += root_size[v];
        }
        else
        {
            root[u] = v;
            root_size[v] += root_size[u];
        }
    }
}

int main(int argc, char **argv)
{
    init_root(5);
    combine_root(1, 2);
    combine_root(2, 3);
    combine_root(3, 4);
    for (int i = 1; i <= 5; i++)
        cout << root[i] << " " << root_size[i] << "\n";
    combine_root(3, 5);
    for (int i = 1; i <= 5; i++)
        cout << root[i] << " " << root_size[i] << "\n";
}