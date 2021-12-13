/// Name: PrimeCheck
/// Description: Checks if given number is prime in O(sqrt(n))
/// Detail: Prime, Primality Test, Maths
/// Guarantee: } // PrimeCheck

bool prime_check(int num)
{
    if (num < 2)
        return 0;
    int sq = (int)sqrt(num) + 1;
    for (int i = 2; i < sq; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
} // PrimeCheck