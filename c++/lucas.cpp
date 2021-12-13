/// Name: Lucas
/// Description: To compute nCr % p when p is small.
/// Detail: ncr, combinatorics, lucas
/// Guarantee: } // Lucas
/// Dependencies: prime_factor, euclid_gcd, chinese_remainder_theorem

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