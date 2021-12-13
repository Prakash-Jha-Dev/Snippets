/// Name: BabyStepGiantLeap
/// Description: Solves the problem of a^x = b%m, where x is unknown.
/// Detail: Maths, Discrete log, Number Theory
/// Guarantee: } // BabyStepGiantLeap
/// Dependencies: modexp

// Reference:cp-algoritms : https://cp-algorithms.com/algebra/discrete-log.html

/*
Solves the problem of a^x = b%m, where x is unknown.
It is also known as problem of discrete log
returns : an integer between 0 to m-1, if such a value of x exists
otherwise returns -1
NOTE: Only works for co-prime a and m
*/

int shanks(int a, int b, int m)
{
    unordered_map<int, int> power;
    int sq = sqrt(m);
    int sqp = modexp(a, sq, m);
    int temp = 1;
    for (int i = 0; i < m; i += sq)
    {
        power[temp] = i;
        temp = (1LL * temp * sqp) % m;
    }
    power[modexp(a, m - 1, m)] = m - 1;

    for (int i = 0; i < sq; i++)
    {
        if (power.count(b))
            return power[b] - i;
        b = (1LL * b * a) % m;
    }
    return -1;
} // BabyStepGiantLeap