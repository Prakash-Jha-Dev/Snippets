#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i, s, n) for (auto i = s; i != n; i++)
#define FORR(i, s, n) for (auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;


template <typename T>
int mobious(T num)
{
    int ans = 1;
    for (T i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            ans *= -1;
            num /= i;
            if (num % i == 0)
                ans = 0;
        }
    }
    if (num > 1)
        ans *= -1;
    return ans;
} // Mobious


int main(int argc, char **argv)
{
    long long x;
    cin>>x;
    cout<<mobious(x);
}