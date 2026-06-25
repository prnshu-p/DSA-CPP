#include <bits/stdc++.h>
class Node
{
public:
    int val;
    Node *left;
    Node *right;

    Node(int data)
    {
        val = data;
        left = right = nullptr;
    }
};

static int idx = -1;
Node *buildTree(std::vector<int> &preOrd)
{
    idx++;
    if (preOrd[idx] == -1)
        return NULL;

    Node *root = new Node(preOrd[idx]);
    root->left = buildTree(preOrd);
    root->right = buildTree(preOrd);

    return root;
}

void topView(Node *root)
{
    std::queue<std::pair<Node *, int>> q;
    std::map<int, int> m;
    q.push({root, 0});

    while (q.size() > 0)
    {
        Node *cur = q.front().first;
        int currHD = q.front().second;
        q.pop();
        
            m[currHD] = cur->val;
        
        if (cur->left != NULL)
            q.push({cur->left, currHD - 1});
        if (cur->right != NULL)
            q.push({cur->right, currHD + 1});
    }

    for(auto i : m)std::cout<<i.second<<" ";

    std::cout<<std::endl;
}

int main()
{
    std::vector<int> preOrd = {5, 6, 3, 2, -1, 1, -1, -1, -1, 0, -1, -1, 7, 8, -1, -1, 9, 10, -1, -1, 11, -1, -1};
    std::vector<int> preOrd2 = {1,2,-1,-1,3,4,-1,-1,5,-1,-1};
    Node *root = buildTree(preOrd2);
    topView(root);
}