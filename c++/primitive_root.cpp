/// Name: PrimitiveRoot
/// Description: Primitive root is a generator in ring of modulo m.
/// Detail: Maths, Number Theory, Modular Ring, Modular Arithmetic
/// Guarantee: } // PrimitiveRoot
/// Dependencies: modexp, prime_factor, totient

/*
Primitive root of a number is such a number which can produce all
other numbers modulo m, when raised to some power p (p belongs to [0,m-1])

There are phi(phi(m)) primitive roots, if there are any.

*/

// checks if given number is primitive root
bool check(int x, int phi, int n, vector<pair<int,int>>& prime_factors)
{
    for(auto z: prime_factors)
    {
        if(modexp(x, phi/z.first, n) == 1) return 0;
    }
    return 1;
}

int primitiveRoot(int n)
{
    int phi = totient(n);
    vector<pair<int,int>>factors = prime_factor(phi);

    for(int i=2; i<n; i++)
    {
        if(__gcd(i,n) == 1 && check(i, phi, n, factors)) return i;
    }
    return -1;
}

vector<int> allPrimitiveRoot(int n)
{
    int x = primitiveRoot(n);
    int phi = totient(n);
    vector<int> primitiveRoots;
    if(x != -1)
    for(int i=1; i<phi; i++)
    {
        if(__gcd(i,phi) == 1) 
            primitiveRoots.push_back(modexp(x,i,n));
    }
    return primitiveRoots;
} // PrimitiveRoot
