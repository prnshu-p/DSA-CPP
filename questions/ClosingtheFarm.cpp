#include <iostream>
#include <vector>
#include <algorithm> // for reverse()

using namespace std;

// --- 1. DSU ENGINE ---
const int MAXN = 200005;
int par[MAXN], sz[MAXN];
int comps = 0; // Starts at 0 because at the "end of time", the farm is empty

void initDSU(int n) {
    for (int i = 1; i <= n; i++) {
        par[i] = i;
        sz[i] = 1;
    }
}

int find(int x) {
    if (x == par[x]) return x;
    return par[x] = find(par[x]); // Path compression
}

bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
    comps--; // Two isolated components merged into one
    return true;
}

// --- 2. MAIN EXECUTION ---
int main() {
    // // REQUIRED for USACO file I/O
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 1-indexed to match USACO barn labels
    vector<vector<int>> adj(n + 1); 
    vector<bool> active(n + 1, false);

    // Read the master blueprint (edges)
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Read the destruction order
    vector<int> q(n);
    for (int i = 0; i < n; i++) {
        cin >> q[i];  
    }
    
    // Initialize DSU
    initDSU(n);
    vector<string> ans;

    // --- 3. THE REVERSE TIME LOOP ---
    // Start from the end of the query array (the last barn closed is the first one opened)
    for (int i = n - 1; i >= 0; i--) {
        int u = q[i];
        
        active[u] = true; // Open the barn
        comps++;          // A new isolated island appears

        // Look at the master blueprint. If a neighbor is already active, unite them.
        for (int neighbor : adj[u]) {
            if (active[neighbor]) {
                unite(u, neighbor); // Automatically handles comps-- if a merge happens
            }
        }

        // After uniting, check if the active farm is fully connected
        if (comps <= 1) {
            ans.push_back("YES");
        } else {
            ans.push_back("NO");
        }
    }

    // --- 4. OUTPUT ---
    // Because we walked backwards, our answers are upside down. Flip them.
    reverse(ans.begin(), ans.end());

    for (string s : ans) {
        cout << s << "\n";
    }

    return 0;
}