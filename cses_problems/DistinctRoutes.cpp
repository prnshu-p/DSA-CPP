#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge {
    int to, cap, flow, rev;
};

int n, m;
vector<vector<Edge>> adj;
vector<int> level, ptr;

void add_edge(int from, int to) {
    adj[from].push_back({to, 1, 0, (int)adj[to].size()});
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

bool find_path(int u, int t, vector<int>& path) {
    path.push_back(u);
    if (u == t) return true;

    for (auto& edge : adj[u]) {
        if (edge.flow == 1) {
            edge.flow = 0;
            if (find_path(edge.to, t, path)) return true;
        }
    }
    path.pop_back();
    return false;
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
        cin >> u >> v;
        add_edge(u, v);
    }

    int k = dinic(1, n);
    cout << k << "\n";

    for (int i = 0; i < k; i++) {
        vector<int> path;
        find_path(1, n, path);
        cout << path.size() << "\n";
        for (int j = 0; j < (int)path.size(); j++) {
            cout << path[j] << (j + 1 == (int)path.size() ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
