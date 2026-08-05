#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> prefs;
vector<vector<int>> adj;
bool reachable[505][505];

void dfs(int start, int current) {
    reachable[start][current] = true;
    for (int next_node : adj[current]) {
        if (!reachable[start][next_node]) {
            dfs(start, next_node);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N)) return 0;

    prefs.resize(N + 1, vector<int>(N));
    adj.resize(N + 1);

    for (int i = 1; i <= N; ++i) {
        bool found_self = false;
        for (int j = 0; j < N; ++j) {
            cin >> prefs[i][j];
            
            if (!found_self) {
                adj[i].push_back(prefs[i][j]);
            }
            if (prefs[i][j] == i) {
                found_self = true;
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        dfs(i, i);
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < N; ++j) {
            int preferred_gift = prefs[i][j];
            
            if (preferred_gift == i) {
                cout << i << "\n";
                break;
            }
            
            if (reachable[preferred_gift][i]) {
                cout << preferred_gift << "\n";
                break;
            }
        }
    }

    return 0;
}