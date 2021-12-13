/// Name: ChineseRemainderTheorem
/// Description: Solves the system of linear congruence equations with given remainder and co-prime modulos
/// Detail: Modular Arithmetic, Linear Congruence, Linear Equation, CRT
/// Guarantee: } // ChineseRemainderTheorem
/// Dependencies: euclid_gcd

int CRT(vector<int> &rem, vector<int> &mod)
{
    long long prod = 1;
    for (auto x : mod)
        prod *= x;

    long long sol = 0;
    for (int i = 0; i < rem.size(); i++)
    {
        // add rem[i]*product such that it becomes zero for all mod[x] except i
        // prod = mod[0]*mod[1]*..*mod[n]
        // rem[i]*(prod/mod[i])*something % mod[x] = 0 for all mod[x] where x!=i
        // something = inverse of prod/mod[i] with mod[i], so overall product becomes (rem[i]*1)%mod[i]
        long long multiplier = ((prod / mod[i]) * inverse((int)(prod / mod[i]), mod[i])) % prod;
        multiplier = (multiplier * rem[i]) % prod;
        sol = (sol + multiplier) % prod;
    }
    return sol;
} // ChineseRemainderTheorem