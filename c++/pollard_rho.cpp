/// Name: PollardRho
/// Description:Flyod Cycle detection to find out a factor and factorize number
/// Detail: Maths, Randomized Algorithm, Number Theory, Cycle detection
/// Guarantee: } // PollardRho
/// Dependencies: modexp

// to simulate next move
template <typename T>
T fun(T num, T mod)
{
    T val = modexp(num, 2, mod) + 1;
    if (val >= mod)
        val -= mod;
    return val;
}

template <typename T>
T pollard_rho(T num)
{
    if (num < 2)
        return num;
    if (num % 2 == 0)
        return 2;

    T sq = sqrt(num) + 2;

    T slow = uniform_int_distribution<int>(3, sq)(rng);
    T fast = slow;
    T gcd = 1;
    int max_iter = 500;

    while (gcd == 1 && max_iter--)
    {
        slow = fun(slow, num);
        fast = fun(fun(fast, num), num);
        gcd = __gcd(abs(slow - fast), num);

        if (gcd != 1)
        {
            if (gcd == num)
            {
                slow = uniform_int_distribution<int>(3, sq)(rng);
                fast = slow;
                gcd = 1;
            }
            else
                break;
        }
    }
    return gcd;
} // PollardRho