// Phase 1: Time Travel & Assigning "Lockers"Before calculating anything, read the entire input
// (starting salaries + future updates + question boundaries).Throw every number into one giant
// list.Store starting salaries.Store future update salaries (x).Store query boundaries (a and
// b).Sort and remove duplicates.
// The Result: You just created a dictionary where every massive
// salary gets a small 1-based "Locker Number" (Index).Crucial Insight: Query boundaries (a and b)
// get lockers too! If no employee actually has that salary, it becomes an empty "ghost locker" (0
// people). This ensures our range math never crashes!

// Phase 2: The Fenwick Tree (Counting)The BIT
// doesn't store salaries. It only stores the count of employees inside each locker.The Translator
// (Binary Search):Whenever the BIT needs to do something, we use a custom function (get_id) to
// Binary Search the dictionary. It translates a massive salary into its tiny Locker Number
// instantly.Executing the Queries (In Order):Update (! k x):Translate old salary to Locker ID
// $\rightarrow$ add(old_locker, -1) (Remove person)Update employee's actual salary variable to
// x.Translate new salary x to Locker ID $\rightarrow$ add(new_locker, +1) (Add person)Question (? a
// b):Translate b to Locker ID. Find prefix sum from Locker 1 up to b.Translate a to Locker ID. Find
// prefix sum from Locker 1 up to a - 1.Output: Sum(b) - Sum(a - 1).

// The 3 Core Code Snippets to Remember.
// 1. The Translator:C++// 
//    Translates $1,000,000 -> Locker 4 auto get_id = [&](int x) {
//     return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
// };
// 2. BIT Update (Climbing UP managers):
//    void add(int locker, int val) {
//     for (; locker <= max_lockers; locker += locker & -locker)
//         tree[locker] += val;
// }
// 3. BIT Query (Jumping DOWN for prefix sum):
//    int query(int locker) {
//     int sum = 0;
//     for (; locker > 0; locker -= locker & -locker)
//         sum += tree[locker];
//     return sum;
// }

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 600005;
int bit[MAXN];
int max_val;

void add(int idx, int val) {
    for (; idx <= max_val; idx += idx & -idx) {
        bit[idx] += val;
    }
}

int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += bit[idx];
    }
    return sum;
}

struct Query {
    char type;
    int a, b;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> s(n + 1);
    vector<int> vals;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        vals.push_back(s[i]);
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].type >> queries[i].a >> queries[i].b;
        if (queries[i].type == '!') {
            vals.push_back(queries[i].b);
        } else {
            vals.push_back(queries[i].a);
            vals.push_back(queries[i].b);
        }
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    max_val = vals.size();

    // Helper lambda function to instantly find the compressed rank of a salary
    auto get_id = [&](int x) {
        // lower_bound finds the index of x. We add 1 because Fenwick trees are 1-based.
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
    };

    for (int i = 1; i <= n; i++) {
        add(get_id(s[i]), 1);
    }

    for (int i = 0; i < q; i++) {
        if (queries[i].type == '!') {
            int k = queries[i].a;
            int x = queries[i].b;

            add(get_id(s[k]), -1);

            s[k] = x;

            add(get_id(s[k]), 1);
        } else {
            int a = queries[i].a;
            int b = queries[i].b;

            cout << query(get_id(b)) - query(get_id(a) - 1) << "\n";
        }
    }

    return 0;
}