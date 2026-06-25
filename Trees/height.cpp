#include <bits/stdc++.h>
class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

static int idx = -1;
Node *buildTree(std::vector<int> &seq)
{
    idx++;
    if (seq[idx] == -1)
        return nullptr;

    Node *root = new Node(seq[idx]);
    root->left = buildTree(seq);
    root->right = buildTree(seq);
}
// void levelOrder(Node *root)
// {
//     int h = 1;
//     std::queue<Node *> q;
//     q.push(root);
//     q.push(nullptr);

//     while (q.size() > 0)
//     {
//         Node *curr = q.front();
//         q.pop();

//         if (curr == nullptr)
//         {
//             if (!q.empty())
//             {
//                 h++;
//                 q.push(nullptr);
//                 std::cout << std::endl;
//             }
//             else
//             {
//                 std::cout << std::endl;
//                 std::cout << "height of tree is = " << h << std::endl;
//                 break;
//             }
//         }
//         else
//         {
//             std::cout << curr->data << " ";
//             if (curr->left != nullptr)
//                 q.push(curr->left);
//             if (curr->right != nullptr)
//                 q.push(curr->right);
//         }
//     }
// }

int height(Node* root){

    if(root==nullptr)return 0;

    int lht = height(root->left);
    int rht = height(root->right);

    return std::max(lht,rht)+1;
}

int main()
{
    std::vector<int> seq = {5, 6, 3, 2, -1, 1, -1, -1, -1, 0, -1, -1, 7, 8, -1, -1, 9, 10, -1, -1, 11, -1, -1};
    Node *root = buildTree(seq);
    std::cout<<height(root)<<std::endl;
    // levelOrder(root);
}
