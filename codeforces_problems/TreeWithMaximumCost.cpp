#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n))
        return 0;

    vector<long long> a(n + 1);
    long long total_weight = 0;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        total_weight += a[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // tree flattening
    vector<int> order;
    queue<int> q;
    vector<int> parent(n + 1, 0);
    vector<long long> depth(n + 1, 0);

    q.push(1);
    order.push_back(1);
    parent[1] = 0;
    depth[1] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
        {
            if (v != parent[u])
            {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                q.push(v);
                order.push_back(v);
            }
        }
    }

    // The Reversal: By calling reverse() on our BFS order,
    // the array now starts with the absolute lowest leaves and ends at the root (City 1).
    reverse(order.begin(), order.end());

    vector<long long> subtree_weight(n + 1, 0);
    long long initial_capital_cost = 0;

    for (int i = 1; i <= n; i++)
    {
        subtree_weight[i] = a[i];                // The Base Cases: We set subtree_weight[i] = a[i] because every city inherently contains its own coins.
        initial_capital_cost += depth[i] * a[i]; // We also calculate the initial_capital_cost (the absolute total cost if City 1 was the permanent HQ) by multiplying every city's coin weight by its distance to City 1.
    }

    for (int u : order)
    {
        if (parent[u] != 0)
        {
            //  every node u takes its total coin weight and dumps it onto its boss's desk:
            subtree_weight[parent[u]] += subtree_weight[u];
        }
    }
    // By the end of this loop, every single city knows the exact weight of all the coins beneath it.

    // We flip the order array back. Now it starts at City 1 and trickles down to the leaves.
    reverse(order.begin(), order.end());

    vector<long long> ans(n + 1, 0);
    ans[1] = initial_capital_cost;

    long long max_cost = ans[1];

    for (int u : order)
    {
        for (int v : adj[u])
        {
            if (v != parent[u])
            {
                // We already know the exact transportation cost for Boss u (ans[u])
                ans[v] = ans[u] - subtree_weight[v] + (total_weight - subtree_weight[v]);
                // If we move the HQ down to Worker v, we don't recalculate the whole map. 
                // We just apply the math:- 
                // subtree_weight[v]: All the coins in $v$'s department just got 1 highway closer. 
                // Subtract their weight from the total cost.+ (total_weight - subtree_weight[v]): 
                // All the coins in the rest of the world just got 1 highway further away. 
                // Add their weight to the total cost.

                // The Answer: We track the absolute maximum cost we see as we shift the HQ around the map.
                max_cost = max(max_cost, ans[v]);
            }
        }
    }
    cout << max_cost << "\n";

return 0;
}