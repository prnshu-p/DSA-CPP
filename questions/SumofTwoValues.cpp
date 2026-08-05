#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<pair<int,int>> val;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        val.push_back({v,i});
    }
 sort(val.begin(), val.end());
    

    int left = 0, right = n - 1;
    int li=-1,ri=-1;
    while (left < right) {
        int curr_val = val[left].first + val[right].first;
        if (curr_val > x) {
            right--;
        } else if (curr_val < x) {
            left++;
        } else {
            li= val[left].second+1,ri= val[right].second+1;
            break;
        }
    }
    if (li == -1) {
        cout << "IMPOSSIBLE" << "\n";
    } else {
        cout << li << " " << ri << "\n";
    }
}
