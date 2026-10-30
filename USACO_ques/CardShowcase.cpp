#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("cardgame.in", "r")) {
        freopen("cardgame.in", "r", stdin);
        freopen("cardgame.out", "w", stdout);
    }

    int n;
    if (!(cin >> n)) return 0;

    vector<int> elsie(n);
    vector<bool> has(2 * n + 1, false);

    for (int i = 0; i < n; i++) {
        cin >> elsie[i];
        has[elsie[i]] = true;
    }

    vector<int> bessie;
    for (int i = 1; i <= 2 * n; i++) {
        if (!has[i]) {
            bessie.push_back(i);
        }
    }

    vector<int> pref(n + 1, 0);
    set<int> high_cards(bessie.begin(), bessie.end());
    int pts = 0;

    for (int i = 0; i < n; i++) {
        auto it = high_cards.upper_bound(elsie[i]);
        if (it != high_cards.end()) {
            pts++;
            high_cards.erase(it);
        } else {
            high_cards.erase(high_cards.begin());
        }
        pref[i + 1] = pts;
    }

    vector<int> suff(n + 2, 0);
    set<int> low_cards(bessie.begin(), bessie.end());
    pts = 0;

    for (int i = n - 1; i >= 0; i--) {
        auto it = low_cards.lower_bound(elsie[i]);
        if (it != low_cards.begin()) {
            pts++;
            --it;
            low_cards.erase(it);
        } else {
            auto last = prev(low_cards.end());
            low_cards.erase(last);
        }
        suff[i + 1] = pts;
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, pref[i] + suff[i + 1]);
    }

    cout << ans << "\n";
    return 0;
}
