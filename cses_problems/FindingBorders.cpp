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

    string s;
    if (!(cin >> s)) return 0;

    int n = s.length();
    auto pi = prefix_function(s);

    vector<int> borders;
    int k = pi[n - 1];
    while (k > 0) {
        borders.push_back(k);
        k = pi[k - 1];
    }

    reverse(borders.begin(), borders.end());
    for (int i = 0; i < (int)borders.size(); i++) {
        cout << borders[i] << (i + 1 == (int)borders.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}
