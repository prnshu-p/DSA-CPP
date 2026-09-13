#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Step 1: The Prefix Sum Array (O(1) range sum lookups)
    // prefix[i] stores the total sum of all slimes from index 0 to i-1
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + a[i];
    }

    // dp[l][r] = absolute minimum cost to merge all slimes from index 'l' to 'r'
    vector<vector<long long>> dp(n, vector<long long>(n, INF));

    // Base Case: A single slime by itself costs 0 energy to merge
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    }

    // Step 2: The Interval DP Engine
    // Loop 1: Expand the size of our testing range (from 2 slimes up to N slimes)
    for (int len = 2; len <= n; len++) {
        
        // Loop 2: Slide the left boundary across the array
        for (int l = 0; l <= n - len; l++) {
    
            // Derive the exact right boundary based on the length
            int r = l + len - 1;

            // Calculate the total size of the final combined slime for this range
            long long range_sum = prefix[r + 1] - prefix[l];

            // Loop 3: Test every single possible split point 'k' between 'l' and 'r'
            for (int k = l; k < r; k++) {
                
                // The Transition: 
                // Cost to merge left side + Cost to merge right side + Cost to combine them both today
                long long current_cost = dp[l][k] + dp[k + 1][r] + range_sum;
                
                // Save the absolute cheapest split point
                dp[l][r] = min(dp[l][r], current_cost);
            }
        }
    }

    // The Final Answer: The minimum cost to merge the entire range from 0 to N-1
    cout << dp[0][n - 1] << "\n";

    return 0;
}