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

// to simulate next move
template <typename T>
T fun(T num, T mod)
{
    T val = modexp(num, 2, mod) + 1;
    if (val >= mod)
        val -= mod;
    return val;
}

template <typename T>
T pollard_rho(T num)
{
    if (num < 2)
        return num;
    if (num % 2 == 0)
        return 2;

    T sq = sqrt(num) + 2;

    T slow = uniform_int_distribution<int>(3, sq)(rng);
    T fast = slow;
    T gcd = 1;
    int max_iter = 500;

    while (gcd == 1 && max_iter--)
    {
        slow = fun(slow, num);
        fast = fun(fun(fast, num), num);
        gcd = __gcd(abs(slow - fast), num);

        if (gcd != 1)
        {
            if (gcd == num)
            {
                slow = uniform_int_distribution<int>(3, sq)(rng);
                fast = slow;
                gcd = 1;
            }
            else
                break;
        }
    }
    return gcd;
} // Pollard Rho

int main(int argc, char **argv)
{
    cout << pollard_rho(1234567);
}