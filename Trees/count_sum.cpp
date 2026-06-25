#include<bits/stdc++.h>
class Node{
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
Node *buildTree(std::vector<int> &seq){
    idx++;
    if (seq[idx] == -1)
        return nullptr;

    Node *root = new Node(seq[idx]);
    root->left = buildTree(seq);
    root->right = buildTree(seq);
}

int count(Node* root){
if(root==nullptr)return 0;

int lc = count(root->left);
int rc = count(root->right);

return lc+rc+1;
}

int sum(Node* root){
if(root==nullptr)return 0;

int ls = sum(root->left);
int rs = sum(root->right);

return ls+rs+root->data;
}

int main(){
    std::vector<int> seq = {5, 6, 3, 2, -1, 1, -1, -1, -1, 0, -1, -1, 7, 8, -1, -1, 9, 10, -1, -1, 11, -1, -1};
    Node *root = buildTree(seq);
    std::cout<<sum(root)<<std::endl;
}