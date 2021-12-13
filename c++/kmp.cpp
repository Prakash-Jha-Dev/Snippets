/// Name: KMP
/// Description: Algorithm to match a given pattern with given string
/// Detail: String, KMP, Maximum Suffix Prefix
/// Guarantee: } // KMP

vector<int> prefix_function(string s)
{
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int kmp(string &s, string &p)
{
    string sp = s + "#" + p;
    auto pre = prefix_function(sp);
    int match = 0;
    for (int i = s.size() + 1; i < sp.size(); i++)
    {
        if (pre[i] == p.size())
            match++;
    }
    return match;
}
