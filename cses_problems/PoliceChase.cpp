#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge {
    int to, cap, flow, rev, id;
};

int n, m;
vector<vector<Edge>> adj;
vector<int> level, ptr;
vector<pair<int, int>> orig_edges;

void add_edge(int from, int to, int id) {
    adj[from].push_back({to, 1, 0, (int)adj[to].size(), id});
    adj[to].push_back({from, 1, 0, (int)adj[from].size() - 1, id});
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

    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    level.resize(n + 1);
    ptr.resize(n + 1);
    orig_edges.resize(m);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        orig_edges[i] = {u, v};
        add_edge(u, v, i);
    }

    int flow = dinic(1, n);
    cout << flow << "\n";

    vector<bool> in_s(n + 1, false);
    queue<int> q;
    q.push(1);
    in_s[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto& edge : adj[u]) {
            if (edge.cap - edge.flow > 0 && !in_s[edge.to]) {
                in_s[edge.to] = true;
                q.push(edge.to);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int u = orig_edges[i].first;
        int v = orig_edges[i].second;
        if (in_s[u] != in_s[v]) {
            cout << u << " " << v << "\n";
        }
    }

    return 0;
}
