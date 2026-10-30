#include <bits/stdc++.h>
using namespace std;

void get_sums(const vector<long long>& a, vector<long long>& sums) {
    int n = a.size();
    sums.reserve(1 << n);
    for (int mask = 0; mask < (1 << n); mask++) {
        long long s = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                s += a[i];
            }
        }
        sums.push_back(s);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int mid = n / 2;
    vector<long long> left_part(a.begin(), a.begin() + mid);
    vector<long long> right_part(a.begin() + mid, a.end());

    vector<long long> s1, s2;
    get_sums(left_part, s1);
    get_sums(right_part, s2);

    sort(s2.begin(), s2.end());

    long long ans = 0;
    for (long long s : s1) {
        long long need = x - s;
        auto range = equal_range(s2.begin(), s2.end(), need);
        ans += (range.second - range.first);
    }

    cout << ans << "\n";
    return 0;
}
