#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<long long>> a(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    // Step 1: Precompute the raw score for every possible standalone team
    // score[mask] = total points if EXACTLY the people in 'mask' form a single group
    vector<long long> score(1 << n, 0);
    
    for (int mask = 0; mask < (1 << n); mask++) {
        long long current_score = 0;
        // Check every unique pair of people in this specific mask
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                for (int j = i + 1; j < n; j++) {
                    if (mask & (1 << j)) {
                        current_score += a[i][j];
                    }
                }
            }
        }
        score[mask] = current_score;
    }

    // Step 2: The DP Engine
    // dp[mask] = maximum total points achievable by dividing the people in 'mask' into ANY number of valid groups
    vector<long long> dp(1 << n, 0);

    for (int mask = 0; mask < (1 << n); mask++) {
        
        // Loop through every valid sub-combination of the current mask
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            
            // TIME MACHINE: 
            // mask ^ sub = The exact people left over if we form a team out of 'sub'.
            // dp[mask ^ sub] = The optimal score already calculated for those leftover people.
            // score[sub] = The raw points we get for making 'sub' a team right now.
            
            dp[mask] = max(dp[mask], dp[mask ^ sub] + score[sub]);
        }
    }

    // The final answer: The absolute maximum score when EVERYONE is grouped optimally
    cout << dp[(1 << n) - 1] << "\n";

    return 0;
}