#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i, s, n) for (auto i = s; i != n; i++)
#define FORR(i, s, n) for (auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;


typedef struct TrieNode
{
    bool isleaf;
    int path = 0;
    int next[26];
} tnode;

vector<tnode> tree;
stack<int> available_tnode;

void pre(int size = 500000)
{
    while(available_tnode.size()) available_tnode.pop();
    tree.resize(size + 5);
    for (int i = tree.size() - 1; i > 0; i--)
        available_tnode.push(i);
}

int getTrieNode()
{
    int tnode = available_tnode.top();
    available_tnode.pop();
    tree[tnode].path = tree[tnode].isleaf = false;
    for (int i = 0; i < 26; i++)
        tree[tnode].next[i] = 0;
    return tnode;
}

int insert(string &s, int curr)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (!tree[curr].next[s[i] - 'a'])
            tree[curr].next[s[i] - 'a'] = getTrieNode();
        curr = tree[curr].next[s[i] - 'a'];
        tree[curr].path++;
    }
    tree[curr].isleaf = true;
    return curr;
}

int search(string &s, int curr)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (!tree[curr].next[s[i] - 'a'])
            return -1;
        curr = tree[curr].next[s[i] - 'a'];
    }
    return curr;
}

int remove(string &s, int curr)
{
    int leafTrieNode = search(s, curr);
    if (leafTrieNode == -1 || !tree[leafTrieNode].isleaf)
        return -1;
    for (int i = 0, prev; i < s.size(); i++)
    {
        prev = curr;
        curr = tree[curr].next[s[i] - 'a'];
        if ((--tree[curr].path) == 0)
        {
            tree[prev].next[s[i] - 'a'] = 0;
            available_tnode.push(curr);
        }
    }
    tree[curr].isleaf = 0;
    return 0;
} // Trie

int main(int argc, char **argv)
{
    pre();
    vector< string >arr{"apple", "ape", "ball", "app"};
    int root = getTrieNode();
    insert(arr[0], root);
    insert(arr[1], root);
    int idx = search(arr[0], root);
    cout<<(idx != -1 && tree[idx].isleaf)<<"\n";
    idx = search(arr[3], root);
    cout<<(idx != -1 && tree[idx].isleaf)<<"\n";
    remove(arr[0], root);
    cout<<(idx != -1 && tree[idx].isleaf)<<"\n";
}