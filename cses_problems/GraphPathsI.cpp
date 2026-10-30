#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int n, m;
long long k;

struct Matrix {
    vector<vector<long long>> mat;
    Matrix(int sz) : mat(sz, vector<long long>(sz, 0)) {}
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    int sz = a.mat.size();
    Matrix res(sz);
    for (int i = 0; i < sz; i++) {
        for (int p = 0; p < sz; p++) {
            if (a.mat[i][p] == 0) continue;
            for (int j = 0; j < sz; j++) {
                res.mat[i][j] = (res.mat[i][j] + a.mat[i][p] * b.mat[p][j]) % MOD;
            }
        }
    }
    return res;
}

Matrix power(Matrix a, long long p) {
    int sz = a.mat.size();
    Matrix res(sz);
    for (int i = 0; i < sz; i++) res.mat[i][i] = 1;
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

    Matrix adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj.mat[u][v] = (adj.mat[u][v] + 1) % MOD;
    }

    Matrix res = power(adj, k);
    cout << res.mat[0][n - 1] << "\n";
    return 0;
}
