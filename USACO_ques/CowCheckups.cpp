#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<long long> c_A(n + 1, 0);
    vector<long long> c_B(n + 1, 0);

    for (int i = 0; i < n; i++) {
        c_A[a[i]]++;
        c_B[b[i]]++;
    }

    long long S = 0;
    for (int i = 1; i <= n; i++) {
        S += c_A[i] * c_B[i];
    }

    long long total_C = S;

    for (int k = 0; k < (n - 1) / 2; k++) {
        int x1 = a[k];
        S -= c_B[x1];
        c_A[x1]--;

        int x2 = a[n - 1 - k];
        S -= c_B[x2];
        c_A[x2]--;

        int y1 = b[k];
        S -= c_A[y1];
        c_B[y1]--;

        int y2 = b[n - 1 - k];
        S -= c_A[y2];
        c_B[y2]--;

        total_C += S;
    }

    long long base_sum = 0;
    for (long long i = 0; i < n; i++) {
        if (a[i] == b[i]) {
            base_sum += (i * (i + 1)) / 2;
            base_sum += ((n - i - 1) * (n - i)) / 2;
        }
    }

    cout << total_C + base_sum << "\n";

    return 0;
}