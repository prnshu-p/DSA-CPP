#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct Matrix {
    long long mat[2][2];
    Matrix() {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix res;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                res.mat[i][j] = (res.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % MOD;
            }
        }
    }
    return res;
}

Matrix power(Matrix a, long long p) {
    Matrix res;
    res.mat[0][0] = res.mat[1][1] = 1;
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

    long long n;
    if (!(cin >> n)) return 0;

    if (n == 0) {
        cout << 0 << "\n";
        return 0;
    }

    Matrix base;
    base.mat[0][0] = 1;
    base.mat[0][1] = 1;
    base.mat[1][0] = 1;
    base.mat[1][1] = 0;

    Matrix res = power(base, n);
    cout << res.mat[0][1] << "\n";
    return 0;
}
