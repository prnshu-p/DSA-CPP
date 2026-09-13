#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

vector<int> tin;
vector<int> tout;
vector<int> subordinates[MAXN]; 
int badge_counter = 0;          

void walk(int person) {
    tin[person] = ++badge_counter; 
    
    for (int worker : subordinates[person]) {
        walk(worker); 
    }
    
    tout[person] = badge_counter; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    tin.resize(n + 1);
    tout.resize(n + 1);

    for(int i = 2; i <= n; i++){
        int boss;
        cin >> boss;
        subordinates[boss].push_back(i);
    }

    walk(1);

    for(int i = 1; i <= n; i++){
        cout << tout[i] - tin[i] << " ";
    }
    cout << "\n";

    return 0;
}