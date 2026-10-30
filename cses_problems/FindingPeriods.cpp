#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const string& s) {
    int n = s.length();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.length();
    auto z = z_function(s);

    vector<int> periods;
    for (int len = 1; len < n; len++) {
        if (z[len] == n - len) {
            periods.push_back(len);
        }
    }
    periods.push_back(n);

    for (int i = 0; i < (int)periods.size(); i++) {
        cout << periods[i] << (i + 1 == (int)periods.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}
