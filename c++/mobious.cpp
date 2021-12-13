/// Name: Mobious
/// Description: Computes the mobious function for given number
/// Detail: Squarefree number, Prime, Divisors, Maths
/// Guarantee: } // Mobious

template <typename T>
int mobious(T num)
{
    int ans = 1;
    for (T i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            ans *= -1;
            num /= i;
            if (num % i == 0)
                ans = 0;
        }
    }
    if (num > 1)
        ans *= -1;
    return ans;
} // Mobious