#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

void PreOrderRecur(TreeNode *root);
void InOrderRecur(TreeNode *root);
void PosOrderRecur(TreeNode *root);

void PreOrder(TreeNode *root);
void InOrder(TreeNode *root);
void PosOrder(TreeNode *root);

int main()
{
    TreeNode A1(1);
    TreeNode A2(2);
    TreeNode A3(3);
    TreeNode A4(4);
    TreeNode A5(5);
    TreeNode A6(6);
    TreeNode A7(7);

    A1.left = &A2;
    A1.right = &A3;
    A2.left = &A4;
    A2.right = &A5;
    A3.left = &A6;
    A3.right = &A7;

    cout << "preorder: " << endl;
    PreOrderRecur(&A1);
    cout << endl;
    PreOrder(&A1);
    cout << endl;
    cout << "inorder: " << endl;
    InOrderRecur(&A1);
    cout << endl;
    InOrder(&A1);
    cout << endl;
    cout << "posorder: " << endl;
    PosOrderRecur(&A1);
    cout << endl;
    PosOrder(&A1);
    cout << endl;
    return 0;
}

void PreOrderRecur(TreeNode *root)
{
    if(root==nullptr) return;
    cout << root->val << ",";
    PreOrderRecur(root->left);
    PreOrderRecur(root->right);
}

void InOrderRecur(TreeNode *root)
{
    if(root==nullptr) return;
    InOrderRecur(root->left);
    cout << root->val << ",";
    InOrderRecur(root->right);
}

void PosOrderRecur(TreeNode *root)
{
    if(root==nullptr) return;
    PosOrderRecur(root->left);
    PosOrderRecur(root->right);
    cout << root->val << ",";
}

void PreOrder(TreeNode *root)
{
    if(root==nullptr) return;
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty())
    {
        TreeNode *cur = s.top();
        s.pop();
        cout << cur->val << ",";
        if(cur->right!=nullptr) s.push(cur->right);
        if(cur->left!=nullptr) s.push(cur->left);
    }
}

void InOrder(TreeNode *root)
{
    if(root==nullptr) return;
    stack<TreeNode*> s;
    TreeNode *cur = root;
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
            cout << cur->val << ",";
            cur = cur->right;
        }
    }
}

void PosOrder(TreeNode *root)
{
    if(root==nullptr) return;
    stack<TreeNode*> s1, s2;
    s1.push(root);
    while(!s1.empty())
    {
        TreeNode *cur = s1.top();
        s1.pop();
        s2.push(cur);
        if(cur->left!=nullptr) s1.push(cur->left);
        if(cur->right!=nullptr) s1.push(cur->right);
    }
    while(!s2.empty())
    {
        TreeNode *cur = s2.top();
        s2.pop();
        cout << cur->val << ",";
    }
}
