#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x),left(nullptr),right(nullptr){}
};

bool isCBT(TreeNode *root);
void levelTraversal(TreeNode *root);
int main()
{
    TreeNode A1(1);
    TreeNode A2(2);
    TreeNode A3(3);
    TreeNode A4(4);
    TreeNode A5(5);
    TreeNode A6(6);
    TreeNode A7(7);
    TreeNode A8(8);
    TreeNode A9(9);
    TreeNode A10(10);
    TreeNode A11(11);

    A1.left = &A2;
    A1.right = &A3;
    A2.left = &A4;
    A2.right = &A5;
    A3.left = &A6;
    A3.right = &A7;
    A4.left = &A8;
    A4.right = &A9;
    A7.left = &A10;
    
  //  levelTraversal(&A1);
    bool res = isCBT(&A1);
    cout << res << endl;
    return 0;
}

//按层遍历，只需要一个队列就可以了，把每一层放到一个vector<int>中，
//把整棵树放到vector<vector<int>>中需要两个队列交替使用
void levelTraversal(TreeNode *root)
{
    if(root==nullptr) return;
    queue<TreeNode*> q;
    TreeNode *cur = root;
    q.push(cur);
    while(!q.empty())
    {
        cur = q.front();
        q.pop();
        cout << cur->val << " ";
        if(cur->left) q.push(cur->left);
        if(cur->right) q.push(cur->right);
    }
}

bool isCBT(TreeNode *root)
{
    if(root==nullptr) return true;
    queue<TreeNode*> q;
    bool leaf = false;
    TreeNode *cur = root;
    q.push(cur);
    while(!q.empty())
    {
        cur = q.front();
        q.pop();
        //如果没有左孩子有右孩子则返回false
        if(cur->left==nullptr && cur->right!=nullptr) return false;
        //如果开启了那个阶段(两个孩子不是都全)后，不是叶节点就返回false
        if(leaf && (cur->left!=nullptr || cur->right!=nullptr)) return false;
        if(cur->left!=nullptr) q.push(cur->left);
        if(cur->right!=nullptr) q.push(cur->right);
        else //有左没右，左右都没有，两个孩子不是都全
        {
            leaf = true;
        }
    }
    return true;
}
