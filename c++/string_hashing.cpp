/// Name: StringHashing
/// Description: Function to hash a string into pair of int, by polynomial hash
/// Detail: String, Hash
/// Guarantee: } // StringHashing

vector<long long> pow31, pow29;

void pre_calc_pow(int n)
{
    pow31.resize(n + 1);
    pow31[0] = 1;
    for (int i = 1; i < n; i++)
    {
        pow31[i] = (pow31[i - 1] * 31) % MOD;
    }
    pow29.resize(n + 1);
    pow29[0] = 1;
    for (int i = 1; i < n; i++)
    {
        pow29[i] = (pow29[i - 1] * 29) % MOD2;
    }
}

pair<int,int> get_hash(string &s)
{
    pair<int,int>pval;
    long long val = 0;
    for (int i = 0; i < s.size(); i++)
    {
        val = (val + (1LL * (s[i] ^ 96) * pow31[i])) % MOD;
    }
    pval.first = val;
    val = 0;
    for (int i = 0; i < s.size(); i++)
    {
        val = (val + (1LL * (s[i] ^ 96) * pow29[i])) % MOD2;
    }
    pval.second = val;
    return pval;
} // StringHashing