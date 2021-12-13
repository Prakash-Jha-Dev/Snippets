#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i, s, n) for (auto i = s; i != n; i++)
#define FORR(i, s, n) for (auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;


void divisor_sieve(vector< vector<int> > &divisor, int size)
{
    divisor.resize(size + 1);
    for (int i = 1; i <= size; i++)
    {
        for (int j = i; j <= size; j += i)
            divisor[j].push_back(i);
    }
} // DivisorSieve

int main(int argc, char **argv)
{
    vector< vector<int> >divi(10);
    divisor_sieve(divi, 10);
    FOR(i, 1, 10)
    {
        cout<<"Divisors of "<<i<<" : ";
        FOR(j,0,divi[i].size()) cout<<divi[i][j]<<" "; cout<<"\n";
    }
}