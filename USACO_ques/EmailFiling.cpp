#include <iostream>
#include <vector>
#include <set>

using namespace std;

void solve() {
    int M, N, K;
    cin >> M >> N >> K;
    
    vector<int> target(N + 1);
    vector<int> unfiled(M + 1, 0);
    
    for (int i = 1; i <= N; i++) {
        cin >> target[i];
        unfiled[target[i]]++;
    }
    
    int f_L = 1;
    int f_R = min(M, K);
    int bottom_reached = 0;
    
    set<int> window_emails;
    set<int> skipped_emails;
    set<int> fileable_emails;
    vector<set<int>> window_by_folder(M + 1);
    
    auto add_to_window = [&](int e) {
        window_emails.insert(e);
        window_by_folder[target[e]].insert(e);
        if (target[e] >= f_L && target[e] <= f_R) {
            fileable_emails.insert(e);
        }
    };
    
    auto remove_from_window = [&](int e) {
        window_emails.erase(e);
        window_by_folder[target[e]].erase(e);
        fileable_emails.erase(e);
    };
    
    for (int i = 1; i <= min(N, K); i++) {
        bottom_reached = i;
        add_to_window(i);
    }
    
    bool possible = true;
    
    while (true) {
        if (!fileable_emails.empty()) {
            int e = *fileable_emails.begin();
            remove_from_window(e);
            unfiled[target[e]]--;
            
            if (bottom_reached < N) {
                bottom_reached++;
                add_to_window(bottom_reached);
            } else if (!skipped_emails.empty()) {
                auto it = prev(skipped_emails.end());
                int pulled = *it;
                skipped_emails.erase(it);
                add_to_window(pulled);
            }
            continue;
        }
        
        if (unfiled[f_L] == 0) {
            f_L++;
            if (f_L > M) {
                break;
            }
            
            int old_f_R = f_R;
            f_R = min(M, f_L + K - 1);
            
            for (int F = old_f_R + 1; F <= f_R; F++) {
                for (int e : window_by_folder[F]) {
                    fileable_emails.insert(e);
                }
            }
            continue;
        }
        
        if (bottom_reached == N) {
            possible = false;
            break;
        }
        
        int top_e = *window_emails.begin();
        remove_from_window(top_e);
        skipped_emails.insert(top_e);
        
        bottom_reached++;
        add_to_window(bottom_reached);
    }
    
    if (possible) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}