/// Name: FactorizePollardRho
/// Description: Factorization Algorithm based on pollard rho to detect factor
/// Detail: Maths, Factorize, Randomized Algorithm, Number Theory, Cycle detection
/// Guarantee: } // FactorizePollardRho
/// Dependencies: pollard_rho, miller_rabin

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
} // FactorizePollardRho