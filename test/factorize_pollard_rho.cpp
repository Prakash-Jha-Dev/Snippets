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

template <typename T>
vector<pair<T, int>> factorize(T num)
{
    vector<pair<T, int>> factors;

    while (num > 1)
    {
        T factor = num;
        while (!miller_rabin(factor))
            factor = pollard_rho(factor);

        int cnt = 1;
        num /= factor;
        while (num % factor == 0)
        {
            num /= factor;
            cnt++;
        }

        factors.push_back({factor, cnt});
    }
    return factors;
} // Factorize Pollard Rho

int main(int argc, char **argv)
{
    auto fac = factorize(12345678);
    for (auto x : fac)
        cout << x.first << " " << x.second << "\n";
}