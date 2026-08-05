#include <bits/stdc++.h>
using namespace std;

// 1. CONSTANTS & TABLE
const int MAXN = 200005; // Maximum number of nodes
const int LOG = 20;      // 2^19 is 524,288 (covers MAXN)

// up[v][j] stores the 2^j-th ancestor of node v.
// Global arrays in C++ are automatically filled with 0s!
int up[MAXN][LOG]; 

// 2. THE QUERY FUNCTION (O(log N))
int get_kth_ancestor(int node, int k) {
    for (int j = 0; j < LOG; j++) {
        if (k & (1 << j)) {         // If the j-th bit of K is turned on...
            node = up[node][j];     // ...take the 2^j step elevator!
        }
    }
    // Optional: Return -1 if the node jumped past the CEO (node became 0)
    return (node == 0) ? -1 : node; 
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    // 3. READ BASE CASES (The 1st bosses)
    // Assuming 1-based indexing and Node 1 is the Root/CEO.
    // up[1][0] remains 0.
    for (int v = 2; v <= n; v++) {
        cin >> up[v][0]; 
    }

    // 4. BUILD THE ELEVATORS (O(N log N))
    // CRITICAL: Jump size (j) on the OUTSIDE, workers (v) on the INSIDE.
    for (int j = 1; j < LOG; j++) {
        for (int v = 1; v <= n; v++) {
            int halfway = up[v][j - 1];
            up[v][j] = up[halfway][j - 1];
        }
    }

    // 5. PROCESS QUERIES
    for (int i = 0; i < q; i++) {
        int node, k;
        cin >> node >> k;
        cout << get_kth_ancestor(node, k) << "\n";
    }

    return 0;
}