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
void levelOrder(Node *root)
{
    std::queue<Node *> q;
    q.push(root);

    while (q.size() > 0)
    {
        Node *curr = q.front();
        q.pop();
        std::cout << curr->val << " ";
        if (curr->left != nullptr)
            q.push(curr->left);
        if (curr->right != nullptr)
            q.push(curr->right);
    }
}

int sumTree(Node *root)
{
    if(root == nullptr) return 0;
    
    int oldVal = root->val;

    if(root->left == nullptr && root->right == nullptr)
    {
        root->val = 0;
        return oldVal;
    }
    
    int ls = sumTree(root->left);
    int rs = sumTree(root->right);
    
    root->val = ls + rs;
    
    return oldVal + ls + rs;
int main()
{
    std::vector<int> preOrd = {5, 6, 3, 2, -1, 1, -1, -1, -1, 0, -1, -1, 7, 8, -1, -1, 9, 10, -1, -1, 11, -1, -1};
    Node *root = buildTree(preOrd);
    levelOrder(root);
    std::cout<<std::endl;
    std::cout << sumTree(root) << std::endl;
    levelOrder(root);
}