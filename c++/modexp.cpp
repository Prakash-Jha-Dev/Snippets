/// Name: ModularExponentiation
/// Description: Computes (base^exp)%mod
/// Detail: Maths, Modular Power
/// Guarantee: } // ModularExponentiation

template <typename T, typename U, typename V>
T modexp(T base, U exp, V mod)
{
    if(exp == 0) return 1;
    base %= mod;
    if(base <= 1) return base;

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