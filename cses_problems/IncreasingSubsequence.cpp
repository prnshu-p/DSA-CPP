#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // This array tracks the smallest possible tail for all increasing subsequences
    vector<int> tails;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        // The Magic: Binary search finds the exact spot where 'x' belongs.
        // It returns an iterator pointing to the first element in 'tails' that is >= x.
        auto it = lower_bound(tails.begin(), tails.end(), x);

        // If 'it' reached the very end, it means 'x' is strictly greater than 
        // every single number currently in 'tails'. 
        // We successfully extend our longest sequence!
        if (it == tails.end()) {
            tails.push_back(x);
        } 
        // If 'it' points to a number inside the array, we OVERWRITE that number with 'x'.
        // This lowers the ceiling and makes it easier for future numbers to attach.
        else {
            *it = x;
        }
    }

    // The physical values inside 'tails' might not be the exact sequence, 
    // but the total LENGTH of 'tails' is mathematically guaranteed to be the right answer.
    cout << tails.size() << "\n";

    return 0;
}