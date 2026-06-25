#include <bits/stdc++.h>
bool isIdentical(TreeNode *p, TreeNode *q){
    if (p == NULL || q == NULL)
        return p == q;

    bool isLeftSame = isIdentical(p->left, q->left);
    bool isRightSame = isIdentical(p->right, q->right);

    return isLeftSame && isRightSame && p->val == q->val;
}

bool isSub(TreeNode *root, TreeNode *subRoot)
{
    if (root == NULL || subRoot == NULL)
        return root == subRoot;

    if (root->val == subRoot->val)
    {
        if (isIdentical(root->left, subRoot->left) && isIdentical(root->right, subRoot->right))
        {
            return true;
        }
    }
    return isSub(root->left, subRoot) || isSub(root->right, subRoot);
}

int main(){
    
}