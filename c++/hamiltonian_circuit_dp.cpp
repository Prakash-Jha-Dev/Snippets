/// Name: HamiltonianCircuitDP
/// Description: Finds a circuit with min cost to travel each vertex exactly once
/// Detail: Hamiltonian Circuit, DP, NP, Bitmask DP, Travelling Salesman
/// Guarantee: } // HamiltonianCircuitDP

#define INF 1e9

string bin(int mask)
{
    bitset<25>tmp(mask);
    return tmp.to_string();
}

vector< vector< double > >dp;

double travel(int pos, int mask, int n, vector<vector<double> >& dist)
{
    if(dp[pos][mask] < INF) return dp[pos][mask];
    if(mask+1 == (1<<n))
    {
        // dp[pos][mask] = dist[pos][1];
        return dist[pos][1];
    }
    for(int i=1;i<=n;i++)
    {
        if(mask&(1<<(i-1))) continue;
        dp[pos][mask] = min(dp[pos][mask], dist[pos][i] + travel(i,mask|(1<<(i-1)),n,dist));
    }
    return dp[pos][mask];
}

double tsp(vector< vector< double > >& dist, int n)
{
    dp.resize(n+1);
    for(int j=1; j<=n; j++)
    {
        dp[j].resize(1<<n);
        fill(dp[j].begin(),dp[j].end(),INF);
    }
    int mask = 1;
    double ans = travel(1,mask,n,dist);
    return ans;
} // HamiltonianCircuitDP
