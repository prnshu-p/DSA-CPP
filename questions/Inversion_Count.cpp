// The Big Misunderstanding
// In the code you provided, you are using the BIT to track the positions of
// an array.  When you write update(i, arr[i]), i is the position in the array (e.g., the 1st
// element, 2nd element, etc.), and you are adding the actual array value to that position.  You
// also use update(a, u) and update(b + 1, -u) for range updates.  
// For the Inversion Count problem,
// we throw that concept entirely out the window. We do not care about the array's positions
// anymore.Instead, the BIT's index represents the actual values of the numbers, and the BIT stores
// frequencies (how many times we've seen that number).The "Bucket" AnalogyImagine the BIT is an
// endless row of buckets, numbered 1, 2, 3, 4, 5... all the way up to $10^7$.Every bucket starts
// completely empty (0).We read our array from right to left. Let's say our array is [3, 1, 2].
// Step1:
//  We look at the last number, 2.Before we do anything with 2, we ask the BIT: "Hey, are there
// any coins in buckets 1 through 1?" (We ask for numbers strictly smaller than 2).The BIT checks
// using sum(1) and says: "No, 0 coins." -> 0 inversions.Now, we drop a single coin into bucket #2
// to say, "I have seen a 2."(In code: update(2, 1))
// Step 2: 
// We look at the next number, 1.We ask the
// BIT: "Are there any coins in bucket 0?" (Numbers strictly smaller than 1).The BIT says: "No, 0
// coins." -> 0 inversions.We drop a single coin into bucket #1 to say, "I have seen a 1."(In code:
// update(1, 1))
// Step 3: 
// We look at the first number, 3.We ask the BIT: "Are there any coins in
// buckets 1 through 2?" (Numbers strictly smaller than 3).The BIT checks using sum(2) and says:
// "Yes, there is 1 coin in bucket #1, and 1 coin in bucket #2. Total = 2 coins." -> 2 inversions.We
// drop a single coin into bucket #3.(In code: update(3, 1))Total Inversions = 2.
#include <iostream>
#include <vector>

using namespace std;

const int MAXA = 10000005;
int bit[MAXA];

void add(int idx, int val) {
    for (; idx < MAXA; idx += idx & -idx) bit[idx] += val;
}

int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) sum += bit[idx];
    return sum;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long inv_count = 0;

    for (int i = n - 1; i >= 0; i--) {
        inv_count += query(a[i] - 1);
        add(a[i], 1);
    }

    cout << inv_count << "\n";

    for (int i = 0; i < n; i++) {
        add(a[i], -1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}