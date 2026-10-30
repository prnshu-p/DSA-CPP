#include <bits/stdc++.h>
using namespace std;

const long long INF = 2e18;

int n, m;
long long k;

struct Matrix {
    vector<vector<long long>> mat;
    Matrix(int sz, long long init_val = INF) : mat(sz, vector<long long>(sz, init_val)) {}
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    int sz = a.mat.size();
    Matrix res(sz, INF);
    for (int p = 0; p < sz; p++) {
        for (int i = 0; i < sz; i++) {
            if (a.mat[i][p] == INF) continue;
            for (int j = 0; j < sz; j++) {
                if (b.mat[p][j] == INF) continue;
                res.mat[i][j] = min(res.mat[i][j], a.mat[i][p] + b.mat[p][j]);
            }
        }
    }
    return res;
}

Matrix power(Matrix a, long long p) {
    int sz = a.mat.size();
    Matrix res(sz, INF);
    for (int i = 0; i < sz; i++) res.mat[i][i] = 0;
    while (p > 0) {
        if (p & 1) res = multiply(res, a);
        a = multiply(a, a);
        p >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m >> k)) return 0;

    Matrix adj(n, INF);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        u--; v--;
        adj.mat[u][v] = min(adj.mat[u][v], c);
    }

    Matrix res = power(adj, k);
    long long ans = res.mat[0][n - 1];
    if (ans >= INF / 2) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}
