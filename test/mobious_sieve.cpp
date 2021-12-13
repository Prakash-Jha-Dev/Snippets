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
} // PrimeSieve

void mobious_sieve(vector<int> &mobious, int size)
{
    vector<int> isprime;
    prime_sieve(isprime, size);

    mobious.resize(size + 1);
    mobious.assign(size + 1, 1);
    for (int i = 2; i <= size; i++)
    {
        if (isprime[i])
        {
            for (int j = i; j <= size; j += i)
                mobious[j] *= -1;

            if (1LL * i * i > size)
                continue;

            int sqr = i * i;
            for (int j = sqr; j <= size; j += sqr)
                mobious[j] = 0;
        }
    }
} // MobiousSieve

int main(int argc, char **argv)
{
    vector<int> mob(10);
    mobious_sieve(mob, 10);
    FOR(i, 1, 10)
        cout << mob[i] << " ";
}