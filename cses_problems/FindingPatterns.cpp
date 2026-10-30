#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 500005;

struct Node {
    int next[26];
    int link = 0;
    vector<int> pattern_indices;
    bool visited = false;

    Node() {
        memset(next, 0, sizeof(next));
    }
};

Node trie[MAX_NODES];
int node_cnt = 1;

void insert(const string& p, int idx) {
    int cur = 1;
    for (char c : p) {
        int x = c - 'a';
        if (!trie[cur].next[x]) {
            trie[cur].next[x] = ++node_cnt;
        }
        cur = trie[cur].next[x];
    }
    trie[cur].pattern_indices.push_back(idx);
}

void build_ac() {
    queue<int> q;
    for (int c = 0; c < 26; c++) {
        if (trie[1].next[c]) {
            trie[trie[1].next[c]].link = 1;
            q.push(trie[1].next[c]);
        } else {
            trie[1].next[c] = 1;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int c = 0; c < 26; c++) {
            if (trie[u].next[c]) {
                int v = trie[u].next[c];
                trie[v].link = trie[trie[u].link].next[c];
                q.push(v);
            } else {
                trie[u].next[c] = trie[trie[u].link].next[c];
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int k;
    if (!(cin >> k)) return 0;

    vector<string> patterns(k);
    for (int i = 0; i < k; i++) {
        cin >> patterns[i];
        insert(patterns[i], i);
    }

    build_ac();

    int cur = 1;
    for (char c : s) {
        cur = trie[cur].next[c - 'a'];
        trie[cur].visited = true;
    }

    vector<vector<int>> link_tree(node_cnt + 1);
    for (int i = 2; i <= node_cnt; i++) {
        link_tree[trie[i].link].push_back(i);
    }

    vector<int> bfs_order;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        bfs_order.push_back(u);
        for (int v : link_tree[u]) {
            q.push(v);
        }
    }

    for (int i = (int)bfs_order.size() - 1; i >= 0; i--) {
        int u = bfs_order[i];
        for (int v : link_tree[u]) {
            if (trie[v].visited) {
                trie[u].visited = true;
            }
        }
    }

    vector<bool> ans(k, false);
    for (int i = 1; i <= node_cnt; i++) {
        if (trie[i].visited) {
            for (int idx : trie[i].pattern_indices) {
                ans[idx] = true;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        cout << (ans[i] ? "YES" : "NO") << "\n";
    }

    return 0;
}
