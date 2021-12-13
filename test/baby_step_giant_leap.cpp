#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i, s, n) for (auto i = s; i != n; i++)
#define FORR(i, s, n) for (auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;

template <typename T, typename U, typename V>
T modexp(T base, U exp, V mod)
{
    T res = 1;
    while (exp)
    {
        if (exp & 1)
            res = (1LL * res * base) % mod;
        base = (1LL * base * base) % mod;
        exp >>= 1;
    }
    return res;
} // ModularExponentiation

// Reference:cp-algoritms : https://cp-algorithms.com/algebra/discrete-log.html

/*
Solves the problem of a^x = b%m, where x is unknown.
It is also known as problem of discrete log
returns : an integer between 0 to m-1, if such a value of x exists
otherwise returns -1
NOTE: Only works for co-prime a and m
*/

int shanks(int a, int b, int m)
{
    unordered_map<int, int> power;
    int sq = sqrt(m);
    int sqp = modexp(a, sq, m);
    int temp = 1;
    for (int i = 0; i < m; i += sq)
    {
        power[temp] = i;
        temp = (1LL * temp * sqp) % m;
    }
    power[modexp(a, m - 1, m)] = m - 1;

    for (int i = 0; i < sq; i++)
    {
        if (power.count(b))
            return power[b] - i;
        b = (1LL * b * a) % m;
    }
    return -1;
} // BabyStepGiantLeap

int main(int argc, char **argv)
{
    cout << shanks(2, 10, 11);
}