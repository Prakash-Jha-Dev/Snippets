/// Name: PrimeDivisorSieve
/// Description: Computes all divisors of all numbers till [1,size]
/// Detail: Prime factors, Divisors, Maths, Sieve
/// Guarantee: } // PrimeDivisorSieve

void prime_divisor_sieve(vector< vector<int> > &divisor, int size)
{
    divisor.resize(size + 1);
    for (int i = 2; i <= size; i++)
    {
        if(divisor[i].size() == 0)
        for (int j = i; j <= size; j += i)
            divisor[j].push_back(i);
    }
} // PrimeDivisorSieve