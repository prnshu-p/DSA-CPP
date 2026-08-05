#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<long long> P(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        long long a;
        cin >> a;
        P[i] = P[i - 1] + a;
    }
    long long S = P[N]; 

    int Q;
    cin >> Q;
    vector<long long> queries(Q);
    for (int i = 0; i < Q; i++) cin >> queries[i];

    map<long long, int> prime_counts;
    long long temp = S;
    
    for (long long i = 2; i * i <= min(temp, 1000000LL); i++) {
        while (temp % i == 0) {
            prime_counts[i]++;
            temp /= i;
        }
    }

    vector<long long> unresolved;
    if (temp > 1) unresolved.push_back(temp);
    vector<long long> final_primes;

    while (!unresolved.empty()) {
        long long val = unresolved.back();
        unresolved.pop_back();
        if (val == 1) continue;

        long long sq = round(sqrt(val));
        if (sq * sq == val) {
            unresolved.push_back(sq);
            unresolved.push_back(sq);
            continue;
        }

        long long split = -1;
        for (long long q : queries) {
            if (S % q == 0) {
                long long g = std::gcd(val, q);
                if (g > 1 && g < val) { split = g; break; }
            }
        }
        if (split == -1) {
            for (int i = 1; i <= N; i++) {
                long long g = std::gcd(val, P[i]);
                if (g > 1 && g < val) { split = g; break; }
            }
        }

        if (split != -1) {
            unresolved.push_back(split);
            unresolved.push_back(val / split);
        } else {
            final_primes.push_back(val);
        }
    }

    for (long long p : final_primes) prime_counts[p]++;

    vector<long long> D = {1};
    for (auto const& [p, count] : prime_counts) {
        int sz = D.size();
        long long multiplier = p;
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < sz; j++) {
                D.push_back(D[j] * multiplier);
            }
            multiplier *= p;
        }
    }
    sort(D.begin(), D.end());

    auto get_idx = [&](long long x) {
        return lower_bound(D.begin(), D.end(), x) - D.begin();
    };

    vector<long long> bucket(D.size(), 0);
    for (int i = 1; i <= N; i++) {
        bucket[get_idx(std::gcd(P[i], S))]++;
    }

    for (auto const& [p, count] : prime_counts) {
        for (int i = D.size() - 1; i >= 0; i--) {
            long long d = D[i];
            if (S / d >= p && S % (d * p) == 0) {
                bucket[i] += bucket[get_idx(d * p)];
            }
        }
    }

    for (int i = 0; i < Q; i++) {
        long long q = queries[i];
        
        if (S % q != 0) {
            cout << -1 << "\n";
        } else {
            long long matching_marks = bucket[get_idx(q)];
            
            long long pieces_we_start_with = N;
            long long pieces_we_want = S / q;
            
            long long erases = pieces_we_start_with - matching_marks;
            long long draws = pieces_we_want - matching_marks;
            
            cout << erases + draws << "\n";
        }
    }
    
    return 0;
}