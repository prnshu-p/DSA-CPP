#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge {
    int to, cap, flow, rev, u_orig, v_orig;
};

int n, m, k;
vector<vector<Edge>> adj;
vector<int> level, ptr;

void add_edge(int from, int to, int u_orig = 0, int v_orig = 0) {
    adj[from].push_back({to, 1, 0, (int)adj[to].size(), u_orig, v_orig});
    adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1, 0, 0});
}

bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto& edge : adj[v]) {
            if (edge.cap - edge.flow > 0 && level[edge.to] == -1) {
                level[edge.to] = level[v] + 1;
                q.push(edge.to);
            }
        }
    }

    return level[t] != -1;
}

int dfs(int v, int t, int pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;

    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
        auto& edge = adj[v][cid];
        int tr = edge.to;
        if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;

        int tr_pushed = dfs(tr, t, min(pushed, edge.cap - edge.flow));
        if (tr_pushed == 0) continue;

        edge.flow += tr_pushed;
        adj[tr][edge.rev].flow -= tr_pushed;
        return tr_pushed;
    }

    return 0;
}

int dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (int pushed = dfs(s, t, INF)) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m >> k)) return 0;

    int s = 0, t = n + m + 1;
    adj.resize(t + 1);
    level.resize(t + 1);
    ptr.resize(t + 1);

    for (int i = 1; i <= n; i++) {
        add_edge(s, i);
    }
    for (int i = 1; i <= m; i++) {
        add_edge(n + i, t);
    }

    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, n + v, u, v);
    }

    int match_count = dinic(s, t);
    cout << match_count << "\n";

    for (int u = 1; u <= n; u++) {
        for (auto& edge : adj[u]) {
            if (edge.to > n && edge.to <= n + m && edge.flow == 1) {
                cout << edge.u_orig << " " << edge.v_orig << "\n";
            }
        }
    }

    return 0;
}
