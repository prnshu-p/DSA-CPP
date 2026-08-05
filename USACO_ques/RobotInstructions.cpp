#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct State {
    long long x, y;
    int steps;
    
    bool operator<(const State& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    
    bool operator==(const State& other) const {
        return x == other.x && y == other.y;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    long long XG, YG;
    cin >> XG >> YG;

    vector<pair<long long, long long>> dirs(N);
    for (int i = 0; i < N; ++i) {
        cin >> dirs[i].first >> dirs[i].second;
    }

    int half1 = N / 2;
    int half2 = N - half1;

    vector<State> left;
    left.reserve(1 << half1);
    
    for (int mask = 0; mask < (1 << half1); ++mask) {
        long long sumX = 0, sumY = 0;
        int steps = 0;
        for (int i = 0; i < half1; ++i) {
            if ((mask >> i) & 1) {
                sumX += dirs[i].first;
                sumY += dirs[i].second;
                steps++;
            }
        }
        left.push_back({sumX, sumY, steps});
    }

    vector<State> right;
    right.reserve(1 << half2);
    
    for (int mask = 0; mask < (1 << half2); ++mask) {
        long long sumX = 0, sumY = 0;
        int steps = 0;
        for (int i = 0; i < half2; ++i) {
            if ((mask >> i) & 1) {
                sumX += dirs[half1 + i].first;
                sumY += dirs[half1 + i].second;
                steps++;
            }
        }
        right.push_back({XG - sumX, YG - sumY, steps});
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    vector<long long> ans(N + 1, 0);
    int i = 0, j = 0;
    int L = left.size(), R = right.size();

    while (i < L && j < R) {
        if (left[i] < right[j]) {
            i++;
        } else if (right[j] < left[i]) {
            j++;
        } else {
            State current = left[i];
            
            vector<long long> countL(half1 + 1, 0);
            vector<long long> countR(half2 + 1, 0);

            while (i < L && left[i] == current) {
                countL[left[i].steps]++;
                i++;
            }

            while (j < R && right[j] == current) {
                countR[right[j].steps]++;
                j++;
            }

            for (int u = 0; u <= half1; ++u) {
                if (countL[u] == 0) continue;
                for (int v = 0; v <= half2; ++v) {
                    if (countR[v] == 0) continue;
                    ans[u + v] += countL[u] * countR[v];
                }
            }
        }
    }

    for (int k = 1; k <= N; ++k) {
        cout << ans[k] << "\n";
    }

    return 0;
}