#include <bits/stdc++.h>
using namespace std;

int lcs(string &s1, string &s2)
{
    vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1));
    for (int i = 1; i <= s1.size(); i++)
    {
        for (int j = 1; j <= s2.size(); j++)
        {
            dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1]));
        }
    }
    /*for(int i=0; i<=s1.size(); i++)
    {
        for(int j=0; j<=s2.size(); j++)
        {
            cout<<dp[i][j]<<" ";
        }
        cout<<"\n";
    }

    int i = s1.size(), j = s2.size();
    cout<<"Matching indexes in string1 :\t";
    while(i > 0 && j > 0)
    {
        if(dp[i-1][j] != dp[i][j-1])
        {
            if(dp[i-1][j] > dp[i][j-1]) i--;
            else j--;
        }
        if(dp[i-1][j-1]+1 == dp[i][j])
        {
            cout<<i<<" ";
        }
        i--;j--;
    }
    cout<<"\n";*/
    return dp[s1.size()][s2.size()];
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;

    cout << lcs(s1, s2) << "\n";
}
