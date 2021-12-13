/// Name: PrimeFactor
/// Description: Decomposes a number into its prime product
/// Detail: Prime, Factors, Divisors, Maths
/// Guarantee: } // PrimeFactor

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

