/// Name: PrimeSieve
/// Description: Computes sieve of prime numbers till [1,size]
/// Detail:  Prime, Primality Test, Maths, Sieve
/// Guarantee: } // PrimeSieve

void prime_sieve(vector<int> &isprime, int size)
{
    isprime.assign(size + 1, 1);
    int sq = (int)sqrt(size) + 1;
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i < sq; i++)
    {
        if (isprime[i])
        {
            for (int j = i * i; j <= size; j += i)
                isprime[j] = 0;
        }
    }
} // PrimeSieve