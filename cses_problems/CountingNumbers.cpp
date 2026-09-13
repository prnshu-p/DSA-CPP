#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

// The Notebook: [index][prev_digit][leading_zero][tight]
// We use 20 for index because 10^18 has up to 19 digits.
long long memo[20][10][2][2];

// The upper limit we are currently building up to
string limit_str;

// The Recursive Generator
long long count_valid(int idx, int prev_digit, bool leading_zero, bool tight) {
    // 1. The Finish Line: If we successfully placed a digit in every space, 
    // we built exactly 1 valid number. We return 1 to count it.
    if (idx == limit_str.length()) {
        return 1;
    }

    // 2. The Cache (The Notebook Lookup): 
    // If we've already solved this exact mathematical state before, 
    // don't recalculate it. Just return the saved answer instantly.
    if (memo[idx][prev_digit][leading_zero][tight] != -1) {
        return memo[idx][prev_digit][leading_zero][tight];
    }

    long long total_valid = 0;

    // 3. The Ceiling: What is the highest digit we can place right now?
    int max_digit = tight ? (limit_str[idx] - '0') : 9;

    // 4. The Loop: Try placing every digit from 0 up to our ceiling
    for (int d = 0; d <= max_digit; d++) {
        
        // 5. THE BOUNCER: If the digit matches the previous one, and it's NOT a phantom zero, skip it!
        if (d == prev_digit && !leading_zero) {
            continue; 
        }

        // 6. Calculate the flags to pass forward to the next space
        bool next_tight = tight && (d == max_digit);
        bool next_leading_zero = leading_zero && (d == 0);
        
        // 7. Move to the next space (idx + 1) and add the results to our total
        total_valid += count_valid(idx + 1, d, next_leading_zero, next_tight);
    }

    // 8. Write the final calculated total into the Notebook before returning it
    return memo[idx][prev_digit][leading_zero][tight] = total_valid;
}

// Wrapper function to set up the engine for a specific number X
long long solve(long long x) {
    // Edge case: If x drops below 0 (like when solving for a-1), there are 0 valid numbers.
    if (x < 0) return 0;
    
    // Convert the massive number X into a string so we can read it digit by digit
    limit_str = to_string(x);
    
    // Wipe the entire Notebook clean with -1s before starting
    memset(memo, -1, sizeof(memo));
    
    // Kick off the generator: start at idx 0, prev_digit doesn't matter (0), 
    // leading_zero is TRUE, and tight is TRUE.
    return count_valid(0, 0, true, true);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long a, b;
    if (cin >> a >> b) {
        // The master math equation: Solve(B) - Solve(A - 1)
        cout << solve(b) - solve(a - 1) << "\n";
    }

    return 0;
}