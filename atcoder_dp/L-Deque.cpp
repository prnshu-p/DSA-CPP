#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // dp[l][r] = The maximum relative score (My Score - Opponent's Score) 
    // the current player can guarantee from the remaining array a[l...r]
    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    // The Interval DP Engine
    // Loop 1: Build by length, starting from 1 up to N
    for (int len = 1; len <= n; len++) {
        
        // Loop 2: Slide the left boundary across the array
        for (int l = 0; l <= n - len; l++) {
            
            // Derive the exact right boundary
            int r = l + len - 1; 

            // Base Case: Only one element left. You are forced to take it.
            if (len == 1) {
                dp[l][r] = a[l];
            } 
            // The Zero-Sum Transition
            else {
                // Choice A: Take the left element (a[l]).
                // The remaining array is [l+1 ... r]. Your opponent gets dp[l+1][r].
                long long take_left = a[l] - dp[l + 1][r];
                
                // Choice B: Take the right element (a[r]).
                // The remaining array is [l ... r-1]. Your opponent gets dp[l][r-1].
                long long take_right = a[r] - dp[l][r - 1];
                
                // You play perfectly, so you take the absolute maximum of your choices
                dp[l][r] = max(take_left, take_right);
            }
        }
    }

    // The Final Answer: The maximum relative score Taro can get starting with the full array
    cout << dp[0][n - 1] << "\n";

    return 0;
}