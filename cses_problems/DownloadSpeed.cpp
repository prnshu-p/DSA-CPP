#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    long long cap, flow;
    int rev;
};

int n, m;
vector<vector<Edge>> adj;
vector<int> level, ptr;

void add_edge(int from, int to, long long cap) {
    adj[from].push_back({to, cap, 0, (int)adj[to].size()});
    adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
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

long long dfs(int v, int t, long long pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;

    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
        auto& edge = adj[v][cid];
        int tr = edge.to;
        if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;

        long long tr_pushed = dfs(tr, t, min(pushed, edge.cap - edge.flow));
        if (tr_pushed == 0) continue;

        edge.flow += tr_pushed;
        adj[tr][edge.rev].flow -= tr_pushed;
        return tr_pushed;
    }

    return 0;
}

long long dinic(int s, int t) {
    long long flow = 0;
    while (bfs(s, t)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (long long pushed = dfs(s, t, INF)) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    level.resize(n + 1);
    ptr.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        add_edge(u, v, c);
    }

    cout << dinic(1, n) << "\n";
    return 0;
}
