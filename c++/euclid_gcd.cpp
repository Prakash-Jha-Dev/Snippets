/// Name: EuclidGCD
/// Description: GCD and Extended GCD 
/// Detail: Maths, GCD, Number Theory
/// Guarantee: } // EuclidGCD

template< typename T, typename U >
long long gcd(T num1, U num2)
{
    return __gcd(num1, num2);
}

/*
* Extended euclid algorithm finds solution to given equation
* Solvng : Sx + Ty = gcd(x,y)
*/
template< typename T, typename U , typename A, typename B>
long long extended_gcd(T x, U y, A& _s, B& _t)
{
    long long s = 0;
    long long old_s = 1;
    long long t = 1;
    long long old_t = 0;
    long long r = x;
    long long old_r = y;

    long long quotient;
    long long temp;
    while(r)
    {
        quotient = old_r / r;

        temp = old_r;
        old_r = r;
        r = temp - quotient*r;

        temp = old_s;
        old_s = s;
        s = temp - quotient*s;

        temp = old_t;
        old_t = t;
        t = temp - quotient*t;
    }
    _t = old_s;
    _s = old_t;
    return old_r;
}


/* Calculates the modular inverse of a number to given co-prime number
* i.e. solves num*x= 1(mod coprime), solves for x
* The idea is to use euclide extended algorithm to find the value of x
* Solvng : Sx + Ty = gcd(x,y)%y
* Sx(mod y) = 1 mod y
*/
template< typename T, typename U >
long long inverse(T x, U y)
{
    long long t = 1;
    long long old_t = 0;
    long long r = x;
    long long old_r = y;

    long long quotient;
    long long temp;
    while(r)
    {
        quotient = old_r / r;

        temp = old_r;
        old_r = r;
        r = temp - quotient*r;

        temp = old_t;
        old_t = t;
        t = temp - quotient*t;
    }
    if(old_t < 0) old_t += y;
    return old_t;
} // EuclidGCD