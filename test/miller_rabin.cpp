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

/**
 * to check if a given number is prime or not
 * uses miller-rabin probablistic algorithm to check if a factor exists in log(n)
 * 
 * param number : Number which is to be checked for primality
 * returns (bool) false if number is not prime, otherwise true
 */
template <typename T>
bool miller_rabin(T number)
{
    if (number < 2)
        return 0;
    // given base_set ensures correctness for numbers in range[2,1e18]
    vector<T> base_set{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; //refer wikipedia for determinstic range and numbers in base_set
    long long d = number - 1;
    int r = __builtin_ctzll(d);
    d >>= r;

    bool not_prime;
    long long val;

    // for every element in base, the test must find the number to be a prime.
    for (long long base : base_set)
    {
        // ensure number used for primality check lies in range [2,number-2] so it satisfies the mathematical reqiurements
        if (base < 2 || base > number - 2)
            continue;

        not_prime = true;
        val = modexp(base, d, number);
        if (val == 1 || val == number - 1)
            continue;
        for (int i = 1; i < r; i++)
        {
            val = (val * val) % number;
            if (val == number - 1)
            {
                not_prime = false;
                break;
            }
        }
        if (not_prime)
            return false;
    }
    return true;
} // Miller Rabin

int main(int argc, char **argv)
{
    FOR(i, 1, 10)
        cout << i << " is prime : " << miller_rabin(i) << "\n";
}