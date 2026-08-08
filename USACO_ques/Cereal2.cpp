#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int to;
    int id;
};

int N, M;
vector<int> F, S;
vector<vector<Edge>> adj;
vector<bool> visited;
vector<bool> edge_used;
vector<bool> bfs_visited;
vector<int> ans_perm;

int cycle_edge;

void find_cycle(int u, int p_edge) {
    visited[u] = true;
    for (auto& edge : adj[u]) {
        if (edge.id == p_edge) continue;
        
        if (visited[edge.to]) {
            if (cycle_edge == -1) {
                cycle_edge = edge.id; 
            }
        } else {
            find_cycle(edge.to, edge.id);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N >> M)) return 0;

    F.resize(N + 1);
    S.resize(N + 1);
    adj.resize(M + 1);
    
    for (int i = 1; i <= N; i++) {
        cin >> F[i] >> S[i];
        adj[F[i]].push_back({S[i], i});
        adj[S[i]].push_back({F[i], i});
    }

    visited.assign(M + 1, false);
    edge_used.assign(N + 1, false);
    bfs_visited.assign(M + 1, false);

    for (int i = 1; i <= M; i++) {
        if (!visited[i] && !adj[i].empty()) {
            cycle_edge = -1;
            find_cycle(i, -1); 

            int root = i; 
            if (cycle_edge != -1) {
                root = F[cycle_edge]; 
                ans_perm.push_back(cycle_edge);
                edge_used[cycle_edge] = true;
            }

            queue<int> q;
            q.push(root);
            bfs_visited[root] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (auto& edge : adj[u]) {
                    if (!edge_used[edge.id]) {
                        edge_used[edge.id] = true;
                        ans_perm.push_back(edge.id);
                        if (!bfs_visited[edge.to]) {
                            bfs_visited[edge.to] = true;
                            q.push(edge.to);
                        }
                    }
                }
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        if (!edge_used[i]) {
            ans_perm.push_back(i);
        }
    }

    vector<bool> taken(M + 1, false);
    int hungry = 0;
    for (int cow : ans_perm) {
        if (!taken[F[cow]]) {
            taken[F[cow]] = true;
        } else if (!taken[S[cow]]) {
            taken[S[cow]] = true;
        } else {
            hungry++;
        }
    }

    cout << hungry << "\n";
    for (int cow : ans_perm) {
        cout << cow << "\n";
    }

    return 0;
}