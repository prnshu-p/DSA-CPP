#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
int n, m;

// This array holds the list of all valid next_masks for any given mask
vector<int> valid_transitions[1024];

// The recursive worker: walks down the rows of a single column
void generate_transitions(int row, int mask, int next_mask) {
    // Base Case: We reached the bottom of the column! 
    // Save this valid next_mask to our list and stop.
    if (row == n) {
        valid_transitions[mask].push_back(next_mask);
        return;
    }

    // Scenario 1: The current square is BLOCKED by a 1 in the mask
    if (mask & (1 << row)) {
        // We skip it. Nothing pokes forward. next_mask gets a 0 here.
        generate_transitions(row + 1, mask, next_mask);
    } 
    // Scenario 2: The current square is EMPTY
    else {
        // Choice A: Lay a horizontal tile.
        // It covers this square, but pokes forward. next_mask gets a 1 here.
        generate_transitions(row + 1, mask, next_mask | (1 << row));
        
        // Choice B: Lay a vertical tile.
        // We can only do this if we aren't at the very bottom (row + 1 < n)
        // AND the square directly below us is also completely empty.
        if (row + 1 < n && !(mask & (1 << (row + 1)))) {
            // It covers both squares perfectly. Nothing pokes forward.
            // next_mask stays 0 for both rows. We skip row + 1 and jump to row + 2.
            generate_transitions(row + 2, mask, next_mask);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    // Precompute all valid transitions for every possible mask (from 0 to 2^N - 1)
    // This way, the worker never has to "think" while walking across the grid.
    for (int mask = 0; mask < (1 << n); mask++) {
        generate_transitions(0, mask, 0);
    }

    // dp[col][mask] = total valid tilings
    vector<vector<long long>> dp(m + 1, vector<long long>(1 << n, 0));
    
    // Base Case: At column 0, there is exactly 1 way to have a perfectly flat wall (mask 0)
    dp[0][0] = 1; 

    // The Notebook Engine: Walk across the room from column 0 to M - 1
    for (int col = 0; col < m; col++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            
            // If this exact situation never happened, skip it
            if (dp[col][mask] == 0) continue;
            
            // Pass the notebook score forward to every valid next_mask!
            for (int next_mask : valid_transitions[mask]) {
                dp[col + 1][next_mask] = (dp[col + 1][next_mask] + dp[col][mask]) % MOD;
            }
        }
    }

    // The Final Answer: Reached column M with a perfectly flat wall (mask 0)
    cout << dp[m][0] << "\n";

    return 0;
}