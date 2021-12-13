#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i, s, n) for (auto i = s; i != n; i++)
#define FORR(i, s, n) for (auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;

bool prime_check(int num)
{
    if (num < 2)
        return 0;
    int sq = (int)sqrt(num) + 1;
    for (int i = 2; i < sq; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
} // Prime Check

int main(int argc, char **argv)
{
    FOR(i, 1, 10)
        cout << i << " is prime : " << prime_check(i) << " \n";
}