#include <bits/stdc++.h>
using namespace std;

int editDistance(string &s1, string &s2)
{
    int delCost, subCost;
    cin >> delCost >> subCost;
    vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1));
    for (int i = 1; i <= s1.size(); i++)
    {
        dp[i][0] = i * delCost;
    }
    for (int i = 1; i <= s2.size(); i++)
    {
        dp[0][i] = i * delCost;
    }

    for (int i = 1; i <= s1.size(); i++)
    {
        for (int j = 1; j <= s2.size(); j++)
        {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = min(min(dp[i - 1][j] + delCost, dp[i][j - 1] + delCost), dp[i - 1][j - 1] + subCost);
        }
    }
    // for(int i=0; i<=s1.size(); i++)
    // {
    //     for(int j=0; j<=s2.size(); j++)
    //     {
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }

    // int i = s1.size(), j = s2.size();
    // cout<<"Procedure:\n";
    // while(i > 0 && j > 0)
    // {
    //     if(dp[i-1][j-1]+subCost == dp[i][j])
    //     {
    //         cout<<"Substitute "<<i<<"th index in s1 with "<<j<<"th index in s2 \n";
    //         i--;j--;
    //     }
    //     else if(dp[i-1][j] + delCost == dp[i][j])
    //     {
    //         cout<<"Delete "<<i<<"th index of s1\n";
    //         i--;
    //     }
    //     else if(dp[i][j-1] + delCost == dp[i][j])
    //     {
    //         cout<<"Delete "<<j<<"th index of s2\n";
    //         j--;
    //     }
    //     else
    //     {
    //         i--;j--;
    //     }
    // }
    // while(i > 0)
    // {
    //     cout<<"Delete "<<i<<"th index of s1\n";
    //     i--;
    // }
    // while(j > 0)
    // {
    //     cout<<"Delete "<<j<<"th index of s2\n";
    //     j--;
    // }

    return dp[s1.size()][s2.size()];
} // EditDistace

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    cout << editDistance(s1, s2) << "\n";
}
