/// Name: NumberTheoriticTransform
/// Description: NTT and Inverse NTT algorithms
/// Detail: Maths, Modular Arithmetic, Polynomial, Multiplication, Pattern, NTT
/// Guarantee: } // NumberTheoriticTransform
/// Dependencies: euclid_gcd

/*
NTT computes the value of polynomial at root^i % mod points
instead of nth root of unity in fft

To compute values for all numbers 1 to mod-1, use primitive root of mod
Divide mod = c*2^k+1, individually do NTT c times for 1,root... root^(c-1)
i.e. compute polynmial for P(x^c), x*P(x^c), ..., x^(c-1)P(x^c)
ref: https://www.codechef.com/viewsolution/27309758
*/

const int mod = 7340033;               //modulo = c*2^k + 1
const int root = 5;                    // primitive root of mod = g^c
const int root_1 = inverse(root, mod); // root inverse required for inverse fft
const int root_pw = 1 << 20;           // root_pw = n = 2^k (increase n to make it to 2^k)

void ntt(vector<int> &a, bool invert)
{
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1)
    {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len)
        {
            int w = 1;
            for (int j = 0; j < len / 2; j++)
            {
                int u = a[i + j], v = (int)(1LL * a[i + j + len / 2] * w % mod);
                a[i + j] = u + v < mod ? u + v : u + v - mod;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert)
    {
        int n_1 = inverse(n, mod);
        for (int &x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
} // NumberTheoriticTransform