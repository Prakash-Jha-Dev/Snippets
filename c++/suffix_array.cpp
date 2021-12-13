/// Name: SuffixArray
/// Description: Ranks the index in lexographical order of suffix starting from it. LCP array is also computed.
/// Detail: Suffix Array, String, LCP, Kasai
/// Guarantee: } // SuffixArray

typedef struct Node
{
    int fr, sr, idx;
    Node(int f = 0, int s = 0, int i = 0)
    {
        fr = f;
        sr = s;
        idx = i;
    }
    bool operator<(const Node &a)
    {
        if (this->fr == a.fr)
            return this->sr < a.sr;
        return this->fr < a.fr;
    }
} node;

// input is string and a grid to store rank of indexes at all level of comparison
void suffixArray(string &s, vector<vector<int>> &data)
{
    data.resize(1 + ceil(log2(s.size())));
    for (auto &z : data)
        z.resize(s.size());
    for (int i = 0; i < s.size(); i++)
        data[0][i] = s[i] - 'a';

    vector<node> temp(s.size());
    for (int step = 1, cnt = 1; cnt < s.size(); step++, cnt *= 2)
    {
        for (int i = 0; i < s.size(); i++)
        {
            temp[i].fr = data[step - 1][i];
            temp[i].sr = i + cnt < s.size() ? data[step - 1][i + cnt] : -1;
            temp[i].idx = i;
        }
        sort(temp.begin(), temp.end());
        data[step][temp[0].idx] = 0;
        for (int i = 1; i < temp.size(); i++)
        {
            if (temp[i].fr == temp[i - 1].fr && temp[i].sr == temp[i - 1].sr)
                data[step][temp[i].idx] = data[step][temp[i - 1].idx];
            else
                data[step][temp[i].idx] = i;
        }
    }
}

// input is string and final rank of indexes from suffix array
vector<int> kasai(string &s, vector<int> &suffix_array)
{
    int n = s.size(), k = 0;
    vector<int> lcp(n, 0);
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[suffix_array[i]] = i;
    for (int i = 0; i < n; i++, k ? k-- : 0)
    {
        if (rank[i] == n - 1)
        {
            k = 0;
            continue;
        }
        int j = suffix_array[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            k++;
        lcp[rank[i]] = k;
    }
    return lcp;
} // SuffixArray