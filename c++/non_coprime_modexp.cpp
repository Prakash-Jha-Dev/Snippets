/// Name: NonCoprimeModularExponentiation
/// Description: Helpful to reduce power in case of tower function. Computes (base^exp)%mod even when gcd(base,mod) != 1.
/// Detail: Maths, Modular Power, Non Coprime modular exponentiation
/// Guarantee: } // NonCoprimeModularExponentiation

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
T non_coprime_modexp(T base, U exp, V mod)
{
    base %= mod;
    if (base <= 1)
        return base;

    T res = 1;
    // phi(mod) is taken as period instead of phi(mod/common_divisor)
    if (exp >= log2(mod * 1.0))
    {
        T phi = totient(mod);
        // x ^ n % m = (x ^ (phi(m) + [n % phi(m)]))%m, when n <= log2(m)
        exp = (exp % phi) + phi;
    }

    for (int i = 1; i <= exp; i++)
    {
        res = (1LL * res * base) % mod;
    }
    return res;
} // NonCoprimeModularExponentiation