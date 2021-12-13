/// Name: DivisorSieve
/// Description: Computes all divisors of all numbers till [1,size]
/// Detail: Factors, Divisors, Maths, Sieve
/// Guarantee: } // DivisorSieve

void divisor_sieve(vector< vector<int> > &divisor, int size)
{
    divisor.resize(size + 1);
    for (int i = 1; i <= size; i++)
    {
        for (int j = i; j <= size; j += i)
            divisor[j].push_back(i);
    }
} // DivisorSieve