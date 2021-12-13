/// Name: Knapsack
/// Description: Computes the optimal value for given cost
/// Detail: DP, Knapsack, NP
/// Guarantee: } // Knapsack

/**
 * w : maximum weight 
 * arr is {value, weight} of all elements
 * 
 * Maximizes the value by choosing a subset of items from available items
 * Modification can be done to choose an item once or more than once
*/
int knapsack(int w, vector<pair<int,int>>&arr)
{
    // create a 1-D grid to store max value till w
    // update in reverse order from max_weight till 0,
    // hence instead of 2-D grid, work in can be done on 1-D grid itself
    vector< int >dp(w+1);
    for(int i=0; i<arr.size(); i++)
    {
        // NOTE
        // If same element can be choosen more than once,
        // update from lower val to higher val
        // If same element can be choosen at most once,
        // update from higher val to lower val
        for(int j=w; j>=arr[i].second; j--)
        {
            dp[j] = max(dp[j] , dp[j-arr[i].second] + arr[i].first);
        }
    }
    return dp[w];
} // Knapsack
