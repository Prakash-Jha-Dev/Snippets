/// Name: LongestIncreasingSubsequence
/// Description: Binary Search based algo to find a maximal set of indices such that a[i] < a[i+1]
/// Detail: LIS, Maths, Algorithm
/// Guarantee: } // LongestIncreasingSubsequence


// look stores the indexes on fly for possible increasing sequences
// before stores the index of element in arr which is part of any increasing subsequence
// NOTE : arr[0] should be -INF

vector<int> longestIncreasingSubsequence(vector<int> &arr)
{
    vector<int> before, look;
    before.resize(arr.size());
    before[0] = -1;
    look.clear();
    look.push_back(0);

    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] > arr[look.back()])
        {
            before[i] = look.back();
            look.push_back(i);
        }
        else
        {
            int l = 0, r = look.size() - 1, m;
            while (l < r)
            {
                m = (l + r + 1) >> 1;
                if (arr[i] > arr[look[m]])
                    l = m;
                else
                    r = m - 1;
            }
            before[i] = look[l];
            look[l + 1] = i;
        }
    }

    vector<int> lis;
    int i = look.back();
    while (i != -1)
    {
        lis.push_back(i);
        i = before[i];
    }
    reverse(lis.begin(), lis.end());
    return lis;
} // LongestIncreasingSubsequence