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

void k_level(Node* root,int lvl){
std::queue<Node*> q;
int k = 1;
q.push(root);
q.push(nullptr);

while(q.size()>0){
    Node* curr = q.front();
    q.pop();

    if(curr==nullptr){
        k++;
        if(!q.empty()){
            q.push(nullptr);
        }else{
            break;
        }
    }else{
        if(k==lvl){
             std::cout<<curr->val<<" ";
            }
          if(curr->left!=nullptr)q.push(curr->left);
          if(curr->right!=nullptr)q.push(curr->right);
    }

}
}

void k_level_rec(Node* root,int k){
    if(root==nullptr)return;
if(k==1){
    std::cout<<root->val<<" ";
    return;
}
k_level_rec(root->left,k-1);
k_level_rec(root->right,k-1);
}

int main(){
std::vector<int> preOrd = {5, 6, 3, 2, -1, 1, -1, -1, -1, 0, -1, -1, 7, 8, -1, -1, 9, 10, -1, -1, 11, -1, -1};
    std::vector<int> preOrd2 = {1,2,-1,-1,3,4,-1,-1,5,-1,-1};
    Node *root = buildTree(preOrd);
    k_level_rec(root,2);
}