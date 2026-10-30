#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> sz;
vector<bool> removed;
vector<char> ans;

void get_sz(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            get_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

int get_centroid(int u, int p, int total) {
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            if (sz[v] > total / 2) {
                return get_centroid(v, u, total);
            }
        }
    }
    return u;
}

void decompose(int u, char rank) {
    get_sz(u, 0);
    int c = get_centroid(u, 0, sz[u]);
    ans[c] = rank;
    removed[c] = true;

    for (int v : adj[c]) {
        if (!removed[v]) {
            decompose(v, rank + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    adj.resize(n + 1);
    sz.resize(n + 1);
    removed.assign(n + 1, false);
    ans.resize(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    decompose(1, 'A');

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
