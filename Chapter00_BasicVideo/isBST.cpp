#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#define INT_MIN -65535
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};
bool isBST(TreeNode *root);

int main()
{
    TreeNode A1(1);
    TreeNode A2(2);
    TreeNode A3(3);
    TreeNode A4(4);

    A3.left = &A2;
    A3.right = &A4;
    A2.left = &A1;

    bool res = isBST(&A1);
    cout << res << endl;
    return 0;
}

bool isBST(TreeNode *root)
{
    if(root==nullptr) return true;
    stack<TreeNode*> s;
    TreeNode *cur = root;
    int pre = INT_MIN;
    while(!s.empty() || cur!=nullptr)
    {
        if(cur!=nullptr)
        {
            s.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = s.top();
            s.pop();
            if(cur->val < pre) return false;
            pre = cur->val;
            cur = cur->right;
        }
    }
    return true;
}
