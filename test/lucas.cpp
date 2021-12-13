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
vector< pair<T, int> > prime_factor(T num)
{
    vector< pair<T, int> >factors;
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



template< typename T, typename U >
long long gcd(T num1, U num2)
{
    return __gcd(num1, num2);
}

/*
* Extended euclid algorithm finds solution to given equation
* Solvng : Sx + Ty = gcd(x,y)
*/
template< typename T, typename U , typename A, typename B>
long long extended_gcd(T x, U y, A& _s, B& _t)
{
    long long s = 0;
    long long old_s = 1;
    long long t = 1;
    long long old_t = 0;
    long long r = x;
    long long old_r = y;

    long long quotient;
    long long temp;
    while(r)
    {
        quotient = old_r / r;

        temp = old_r;
        old_r = r;
        r = temp - quotient*r;

        temp = old_s;
        old_s = s;
        s = temp - quotient*s;

        temp = old_t;
        old_t = t;
        t = temp - quotient*t;
    }
    _t = old_s;
    _s = old_t;
    return old_r;
}


/* Calculates the modular inverse of a number to given co-prime number
* i.e. solves num*x= 1(mod coprime), solves for x
* The idea is to use euclide extended algorithm to find the value of x
* Solvng : Sx + Ty = gcd(x,y)%y
* Sx(mod y) = 1 mod y
*/
template< typename T, typename U >
long long inverse(T x, U y)
{
    long long t = 1;
    long long old_t = 0;
    long long r = x;
    long long old_r = y;

    long long quotient;
    long long temp;
    while(r)
    {
        quotient = old_r / r;

        temp = old_r;
        old_r = r;
        r = temp - quotient*r;

        temp = old_t;
        old_t = t;
        t = temp - quotient*t;
    }
    if(old_t < 0) old_t += y;
    return old_t;
} // EuclidGCD


int CRT(vector<int> &rem, vector<int> &mod)
{
    long long prod = 1;
    for (auto x : mod)
        prod *= x;

    long long sol = 0;
    for (int i = 0; i < rem.size(); i++)
    {
        // add rem[i]*product such that it becomes zero for all mod[x] except i
        // prod = mod[0]*mod[1]*..*mod[n]
        // rem[i]*(prod/mod[i])*something % mod[x] = 0 for all mod[x] where x!=i
        // something = inverse of prod/mod[i] with mod[i], so overall product becomes (rem[i]*1)%mod[i]
        long long multiplier = ((prod / mod[i]) * inverse((int)(prod / mod[i]), mod[i])) % prod;
        multiplier = (multiplier * rem[i]) % prod;
        sol = (sol + multiplier) % prod;
    }
    return sol;
} // ChineseRemainderTheorem


// NOTE: Preprocess from main()
vector<long long> fact;
void factorials(int n, int mod)
{
    fact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = (fact[i - 1] * i) % mod;
}

long long ncr(int n, int r, int mod)
{
    if (n < r)
        return 0;
    return ((((1LL * fact[n] * inverse(fact[r], mod) % mod)) % mod) * inverse(fact[n - r], mod)) % mod;
} // Combinatorics

int Lucas(int n, int r, int p)
{
    long long ans = 1;
    while (n)
    {
        ans = (ans * ncr(n % p, r % p, p)) % p;
        n /= p;
        r /= p;
    }
    return ans;
}

int LucasNonPrime(int n, int r, int p)
{
    auto fac = prime_factor(p);
    vector<int> rem(fac.size()), mod(fac.size());
    for (int i = 0; i < fac.size(); i++)
    {
        int temp = fac[i].first;
        for (int j = 2; j <= fac[i].second; j++)
            temp *= fac[i].first;

        rem[i] = Lucas(n, r, temp);
        mod[i] = temp;
    }

    int sol = CRT(rem, mod);
    return sol;
} // Lucas






int main(int argc, char **argv)
{
    int n, r, p;
    cin >> n >> r >> p;
    factorials(p,p);
    cout << LucasNonPrime(n, r, p);
}