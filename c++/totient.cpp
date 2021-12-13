/// Name: Totient
/// Description: Computes the count of x in [1,num] such that GCD(x,num) = 1
/// Detail: Coprime, Divisors, Maths, GCD, Phi
/// Guarantee: } // Totient

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
