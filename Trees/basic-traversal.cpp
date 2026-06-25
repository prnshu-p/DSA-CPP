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

void preOrder(Node *root)
{
    if (root == nullptr)
        return;

    std::cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}
void inOrder(Node *root)
{
    if (root == nullptr)
        return;

    inOrder(root->left);
    std::cout << root->val << " ";
    inOrder(root->right);
}
void postOrder(Node *root)
{
    if (root == nullptr)
        return;

    postOrder(root->left);
    postOrder(root->right);
    std::cout << root->val << " ";
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

int main()
{
    std::vector<int> preOrd = {5, 6, 3, 2, -1, 1, -1, -1, -1, 0, -1, -1, 7, 8, -1, -1, 9, 10, -1, -1, 11, -1, -1};
    Node *root = buildTree(preOrd);
    preOrder(root);
    std::cout << std::endl;
    inOrder(root);
    std::cout << std::endl;
    postOrder(root);
    std::cout << std::endl;
    levelOrder(root);
    return 0;
}
