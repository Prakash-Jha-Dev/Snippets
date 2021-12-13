#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i, s, n) for (auto i = s; i != n; i++)
#define FORR(i, s, n) for (auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;

void prime_sieve(vector<int> &isprime, int size)
{
    isprime.resize(size + 1);
    isprime.assign(size + 1, 1);
    int sq = (int)sqrt(size) + 1;
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i < sq; i++)
    {
        if (isprime[i])
        {
            for (int j = i * i; j <= size; j += i)
                isprime[j] = 0;
        }
    }
} // Prime Sieve

int main(int argc, char **argv)
{
    vector<int> ps;
    prime_sieve(ps, 10);
    FOR(i, 1, 10)
        cout << i << " is prime : " << ps[i] << "\n";
}