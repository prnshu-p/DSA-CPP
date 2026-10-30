#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int col[MAXN];
vector<int> adj[MAXN];
int sz[MAXN], heavy[MAXN];
int freq[MAXN];
int max_freq = 0;
long long sum_col = 0;
long long ans[MAXN];

void dfs_sz(int u, int p) {
    sz[u] = 1;
    heavy[u] = -1;
    int max_sub = 0;

    for (int v : adj[u]) {
        if (v != p) {
            dfs_sz(v, u);
            sz[u] += sz[v];
            if (sz[v] > max_sub) {
                max_sub = sz[v];
                heavy[u] = v;
            }
        }
    }
}

void add(int u, int p, int big_child) {
    freq[col[u]]++;
    if (freq[col[u]] > max_freq) {
        max_freq = freq[col[u]];
        sum_col = col[u];
    } else if (freq[col[u]] == max_freq) {
        sum_col += col[u];
    }

    for (int v : adj[u]) {
        if (v != p && v != big_child) {
            add(v, u, big_child);
        }
    }
}

void remove(int u, int p) {
    freq[col[u]]--;
    for (int v : adj[u]) {
        if (v != p) {
            remove(v, u);
        }
    }
}

void dfs_sack(int u, int p, bool keep) {
    for (int v : adj[u]) {
        if (v != p && v != heavy[u]) {
            dfs_sack(v, u, false);
        }
    }

    if (heavy[u] != -1) {
        dfs_sack(heavy[u], u, true);
    }

    add(u, p, heavy[u]);
    ans[u] = sum_col;

    if (!keep) {
        remove(u, p);
        max_freq = 0;
        sum_col = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; i++) cin >> col[i];

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_sz(1, 0);
    dfs_sack(1, 0, true);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
