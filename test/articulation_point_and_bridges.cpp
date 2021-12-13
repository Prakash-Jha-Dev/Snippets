#pragma comment(linker,"/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i,s,n) for(auto i = s; i != n; i++)
#define FORR(i,s,n) for(auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;


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


int main(int argc, char** argv)
{
    vector< vector<int> >arr{ {1}, {0,2}, {1,3,4}, {2,5}, {2,5}, {3,4} };
    adj = arr;
    cutPointsandBridges(arr.size());
    cout<<"Articulation Points\n";
    for(auto x: articulationPoint) cout<<x<<" "; cout<<"\n";
    cout<<"Bridges\n";
    for(auto x: bridges) cout<<x.first<<" "<<x.second<<"\n";
}