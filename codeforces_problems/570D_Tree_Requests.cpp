#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

int n, m;
vector<int> adj[MAXN];
char letters[MAXN];
int in_time[MAXN], out_time[MAXN], depth[MAXN];
int timer = 0;

struct Entry {
    int in_t;
    int pref_mask;
};

vector<Entry> depth_list[MAXN];

void dfs(int u, int d) {
    depth[u] = d;
    in_time[u] = ++timer;

    int mask = 1 << (letters[u] - 'a');
    int prev_mask = depth_list[d].empty() ? 0 : depth_list[d].back().pref_mask;
    depth_list[d].push_back({in_time[u], prev_mask ^ mask});

    for (int v : adj[u]) {
        dfs(v, d + 1);
    }
    out_time[u] = timer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        cin >> letters[i];
    }

    dfs(1, 1);

    while (m--) {
        int v, h;
        cin >> v >> h;

        if (h < depth[v] || depth_list[h].empty()) {
            cout << "Yes\n";
            continue;
        }

        auto& vec = depth_list[h];
        auto it_r = upper_bound(vec.begin(), vec.end(), out_time[v], [](int val, const Entry& e) {
            return val < e.in_t;
        });

        auto it_l = lower_bound(vec.begin(), vec.end(), in_time[v], [](const Entry& e, int val) {
            return e.in_t < val;
        });

        int r_idx = it_r - vec.begin() - 1;
        int l_idx = it_l - vec.begin() - 1;

        int mask_r = (r_idx >= 0) ? vec[r_idx].pref_mask : 0;
        int mask_l = (l_idx >= 0) ? vec[l_idx].pref_mask : 0;
        int xor_sum = mask_r ^ mask_l;

        if (__builtin_popcount(xor_sum) <= 1) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
