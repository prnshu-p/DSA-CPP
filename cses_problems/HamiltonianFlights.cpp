#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // We store INCOMING roads instead of outgoing. 
    // This makes it extremely fast to look backwards in time.
    vector<vector<int>> in_adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // Convert to 0-indexed (City 1 becomes City 0, etc.)
        in_adj[v].push_back(u); // Road comes FROM u TO v
    }

    // The DP Table: 2^N rows, N columns
    // dp[mask][u] = number of paths visiting the subset 'mask', currently standing at 'u'
    vector<vector<int>> dp(1 << n, vector<int>(n, 0));

    // Base Case: 1 path to stand at the starting line (City 0) with only City 0 visited
    dp[1][0] = 1;

    // Loop through every possible history (mask)
    for (int mask = 2; mask < (1 << n); mask++) {
        
        // OPTIMIZATION 1: Every valid flight MUST start at City 0. 
        // If Bit 0 is off, this history is impossible.
        if ((mask & (1 << 0)) == 0) continue;

        // OPTIMIZATION 2: The problem states the flight ENDS as soon as you reach City N-1.
        // If our current history includes City N-1, but we haven't visited ALL cities yet,
        // this is an invalid dead-end. Skip it.
        if ((mask & (1 << (n - 1))) && mask != ((1 << n) - 1)) continue;

        // Test every possible city we could be standing in right now
        for (int u = 0; u < n; u++) {
            
            // If the history says we haven't visited 'u', we can't be standing there.
            if ((mask & (1 << u)) == 0) continue; 

            // Time Travel: Figure out what our history was before arriving at 'u'
            int prev_mask = mask - (1 << u); // (Can also be written as mask ^ (1 << u))

            for (int v : in_adj[u]) {
                
                if (prev_mask & (1 << v)) {
                    dp[mask][u] = (dp[mask][u] + dp[prev_mask][v]) % MOD;
                }
            }
        }
    }

    cout << dp[(1 << n) - 1][n - 1] << "\n";

    return 0;
}