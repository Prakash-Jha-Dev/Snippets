/// Name: DiscreteRoot
/// Description: Computes solution to equation of form x^k = b%m where m is prime.
/// Detail: Maths, Number Theory
/// Guarantee: } // DiscreteRoot
/// Dependencies: baby_step_giant_leap, primitive_root
// reference : https://cp-algorithms.com/algebra/discrete-root.html

vector<int> discrete_root(int k, int m, int b)
{
    int g = primitiveRoot(m);
    int p = shanks(g, b, m);

    vector<int> roots;
    int delta = (m - 1) / __gcd(m - 1, k);
    for (int i = p % delta; i < m - 1; i += delta)
        roots.push_back(modexp(g, i, m));
    return roots;
} // DiscreteRoot
