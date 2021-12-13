/// Name: Combinatorics
/// Description: Set of combinatorial algorithms and functions
/// Detail: ncr, npr, factorial, 
/// Guarantee: } // Combinatorics

vector< vector<long long> > ncr_table(int n)
{
    vector< vector<long long> > ncr(n + 1, vector< long long>(n + 1));

    for (int i = 0; i <= n; i++)
        ncr[i][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
            ncr[i][j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % MOD;
    }
    return ncr_table;
}

vector<long long> factorials(int n)
{
    vector<long long> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = (fact[i - 1] * i) % MOD;
    return fact;
}

template <typename T>
long long ncr(int n, int r, vector<T> &fact)
{
    if(n < r) return 0;
    return ((1LL * fact[n] * inverse(fact[r],MOD) % MOD) * inverse(fact[n-r],MOD)) % MOD;
}

template <typename T>
long long npr(int n, int r, vector<T> &fact)
{
    return (1LL * fact[n] * invmod(fact[r])) % MOD;
} // Combinatorics