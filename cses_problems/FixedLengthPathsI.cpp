#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<vector<int>> adj;
vector<int> sz;
vector<bool> removed;
int cnt[200005];
int max_depth;
long long ans = 0;

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

void get_depths(int u, int p, int d, vector<int>& depths) {
    if (d > k) return;
    depths.push_back(d);
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            get_depths(v, u, d + 1, depths);
        }
    }
}

void decompose(int u) {
    get_sz(u, 0);
    int c = get_centroid(u, 0, sz[u]);
    removed[c] = true;

    max_depth = 0;
    cnt[0] = 1;

    for (int v : adj[c]) {
        if (!removed[v]) {
            vector<int> depths;
            get_depths(v, c, 1, depths);
            for (int d : depths) {
                if (k >= d) {
                    ans += cnt[k - d];
                }
            }
            for (int d : depths) {
                cnt[d]++;
                max_depth = max(max_depth, d);
            }
        }
    }

    for (int i = 0; i <= max_depth; i++) {
        cnt[i] = 0;
    }

    for (int v : adj[c]) {
        if (!removed[v]) {
            decompose(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> k)) return 0;

    adj.resize(n + 1);
    sz.resize(n + 1);
    removed.assign(n + 1, false);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    decompose(1);

    cout << ans << "\n";
    return 0;
}
