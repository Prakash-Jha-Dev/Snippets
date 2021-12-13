/// Name: MobiousSieve
/// Description: Computes the mobious function for all numbers till [1,size]
/// Detail: Squarefree number, Prime, Divisors, Maths, Sieve
/// Guarantee: } // MobiousSieve
/// Dependencies: prime_sieve

void mobious_sieve(vector<int> &mobious, int size)
{
    vector<int> isprime;
    prime_sieve(isprime, size);

    mobious.assign(size + 1, 1);
    for (int i = 2; i <= size; i++)
    {
        if (isprime[i])
        {
            for (int j = i; j <= size; j += i)
                mobious[j] *= -1;

            if (1LL * i * i > size)
                continue;

            int sqr = i * i;
            for (int j = sqr; j <= size; j += sqr)
                mobious[j] = 0;
        }
    }
} // MobiousSieve