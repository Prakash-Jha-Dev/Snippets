/// Name: DigitDP
/// Description: Digit dp to calculate count of numbers less than given number with certain property
/// Detail: DP, Digit
/// Guarantee: } // DigitDP

int digit_dp(string ss)
{
    // exploit the property i.e. combine those states whose sum of digit is same
    int n = ss.size();

    // empty suffixes having sum = 0
    // dp[pos][bounded/unboundex][sum]
    dp[n][0][0] = 1;
    dp[n][1][0] = 1;

    for (int i = n - 1; i >= 0; i--)
    {
        for (int tight = 0; tight < 2; tight++)
        {
            for (int sum = 0; sum < 163; sum++)
            {
                if (tight) // suffix <= suffix of given number
                {
                    for (int d = 0; d <= ss[i] - '0'; d++)
                    {
                        dp[i][1][sum] += (d == ss[i] - '0') ? dp[i + 1][1][sum - d] : dp[i + 1][0][sum - d];
                    }
                }
                else // suffix can be any combination of digits
                {
                    for (int d = 0; d < 10; d++)
                    {
                        dp[i][0][sum] += dp[i + 1][0][sum - d];
                    }
                }
            }
        }
    }
    int ans = 0;
    // checking for specific property, here sum of digits must be prime
    // for (int i = 0; i < 200; i++)
    // {
    //     if (isPrime(i))
    //         ans += dp[0][1][i];
    // }
    return ans;
} // DigitDP