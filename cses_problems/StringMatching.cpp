#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string& s) {
    int n = s.length();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, p;
    if (!(cin >> s >> p)) return 0;

    string combined = p + "#" + s;
    auto pi = prefix_function(combined);

    int m = p.length();
    int count = 0;
    for (int i = m + 1; i < (int)combined.length(); i++) {
        if (pi[i] == m) {
            count++;
        }
    }

    cout << count << "\n";
    return 0;
}
