#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<pair<T, int>> prime_factor(T num)
{
    vector<pair<T, int>> factors;
    for (T i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            factors.push_back({i, 0});
            while (num % i == 0)
            {
                num /= i;
                factors.back().second++;
            }
        }
    }
    if (num > 1)
        factors.push_back({num, 1});

    return factors;
} // PrimeFactor

template <typename T>
T totient(T num)
{
    T ans = num;
    for (T i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            ans -= ans / i;
            while (num % i == 0)
                num /= i;
        }
    }
    if (num > 1)
        ans -= ans / num;
    return ans;
} // Totient

template <typename T, typename U, typename V>
T modexp(T base, U exp, V mod)
{
    if (exp == 0)
        return 1;
    base %= mod;
    if (base <= 1)
        return base;

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

/*
Primitive root of a number is such a number which can produce all
other numbers modulo m, when raised to some power p (p belongs to [0,m-1])

There are phi(phi(m)) primitive roots, if there are any.

*/

// checks if given number is primitive root
bool check(int x, int phi, int n, vector<pair<int, int>> &prime_factors)
{
    for (auto z : prime_factors)
    {
        if (modexp(x, phi / z.first, n) == 1)
            return 0;
    }
    return 1;
}

int primitiveRoot(int n)
{
    int phi = totient(n);
    vector<pair<int, int>> factors = prime_factor(phi);

    for (int i = 2; i < n; i++)
    {
        if (__gcd(i, n) == 1 && check(i, phi, n, factors))
            return i;
    }
    return -1;
}

vector<int> allPrimitiveRoot(int n)
{
    int x = primitiveRoot(n);
    int phi = totient(n);
    vector<int> primitiveRoots;
    if (x != -1)
        for (int i = 1; i < phi; i++)
        {
            if (__gcd(i, phi) == 1)
                primitiveRoots.push_back(modexp(x, i, n));
        }
    return primitiveRoots;
} // PrimitiveRoot

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

vector<int> discrete_root(int k, int m, int b)
{
    int g = primitiveRoot(m);
    int p = shanks(g, b, m);

    vector<int> roots;
    int delta = (m - 1) / __gcd(m - 1, k);
    for (int i = (p % delta); i < m - 1; i += delta)
        roots.push_back(modexp(g, i, m));
    return roots;
}

/* Input
3 13 12
*/

/* Output
4 12 10
*/

int main()
{
    int k, m, b;
    cin >> k >> m >> b;

    auto ans = discrete_root(k, m, b);
    for (auto x : ans)
        cout << x << " ";
}
