#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x; 
    cin >> n >> x;

    vector<long long> weight(n);
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    // dp[mask] = {minimum_rides, current_elevator_weight}
    // Size is 2^N to hold every possible group of people
    vector<pair<int, long long>> dp(1 << n);
    
    // Base Case: 0 people require 1 empty ride holding 0 weight
    dp[0] = {1, 0};

    // Build the scoreboard from 1 up to (2^N - 1)
    for (int mask = 1; mask < (1 << n); mask++) {
        
        // Default worst-case scenario: Everyone takes their own separate ride
        dp[mask] = {n + 1, 0}; 

        // Test every person to see who walked in last
        for (int p = 0; p < n; p++) {
            
            // If Person 'p' is actually in this current group
            if (mask & (1 << p)) {
                
                // TIME MACHINE: Get the score before Person 'p' joined
                int prev_mask = mask ^ (1 << p);
                int rides = dp[prev_mask].first;
                long long curr_weight = dp[prev_mask].second;

                // Test if Person 'p' fits in that past elevator
                if (curr_weight + weight[p] <= x) {
                    curr_weight += weight[p]; // They fit
                } else {
                    rides++;                  // They don't fit, start a new ride
                    curr_weight = weight[p];
                }

                // C++ magic: min() automatically compares 'rides' first. 
                // If 'rides' are tied, it compares 'curr_weight' to leave the most room.
                dp[mask] = min(dp[mask], {rides, curr_weight});
            }
        }
    }

    // The final answer: The number of rides for the mask where EVERYONE is present
    cout << dp[(1 << n) - 1].first << "\n";

    return 0;
}