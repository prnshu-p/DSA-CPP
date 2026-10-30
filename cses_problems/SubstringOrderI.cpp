#include <bits/stdc++.h>
using namespace std;

vector<int> build_suffix_array(const string& s) {
    int n = s.length();
    vector<int> sa(n), rank(n), temp(n);

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = (unsigned char)s[i];
    }

    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = (i + k < n) ? rank[i + k] : -1;
            int rj = (j + k < n) ? rank[j + k] : -1;
            return ri < rj;
        };

        sort(sa.begin(), sa.end(), cmp);

        temp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            temp[sa[i]] = temp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        rank = temp;
        if (rank[sa[n - 1]] == n - 1) break;
    }

    return sa;
}

vector<int> build_lcp(const string& s, const vector<int>& sa) {
    int n = s.length();
    vector<int> rank(n, 0), lcp(n, 0);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if (k > 0) k--;
    }

    return lcp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    long long k;
    if (!(cin >> s >> k)) return 0;

    int n = s.length();
    auto sa = build_suffix_array(s);
    auto lcp = build_lcp(s, sa);

    for (int i = 0; i < n; i++) {
        int prev_lcp = (i == 0 ? 0 : lcp[i - 1]);
        long long new_substrings = (n - sa[i]) - prev_lcp;

        if (k <= new_substrings) {
            int len = prev_lcp + k;
            cout << s.substr(sa[i], len) << "\n";
            return 0;
        }
        k -= new_substrings;
    }

    return 0;
}
