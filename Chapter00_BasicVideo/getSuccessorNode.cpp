#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), parent(nullptr), left(nullptr), right(nullptr){}
};

TreeNode* getLeftMost(TreeNode *head);
TreeNode* getSuccessorNode(TreeNode *node);
TreeNode* getRightMost(TreeNode *head);
TreeNode* getPredecessorNode(TreeNode *node);

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
    A2.parent = &A1;
    A3.left = &A6;
    A3.right = &A7;
    A3.parent = &A1;
    A4.parent = &A2;
    A5.parent = &A2;
    A6.parent = &A3;
    A7.parent = &A3;
    cout << "Successor Node:" << endl;
    TreeNode* node = getSuccessorNode(&A4);
    cout << (node==nullptr?0:node->val) << endl;
    cout << "Predecessor Node:" << endl;
    node = getPredecessorNode(&A4);
    cout << (node==nullptr?0:node->val) << endl;
    return 0;
}

TreeNode* getSuccessorNode(TreeNode *node)
{
    if(node==nullptr) return node;
    if(node->right!=nullptr) return getLeftMost(node->right);
    else
    {
        TreeNode *parent = node->parent;
        while(parent!=nullptr && parent->left!=node)
        {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
}

TreeNode* getPredecessorNode(TreeNode *node)
{
    if(node==nullptr) return node;
    //如果有左子树，那么前驱节点就是其左子树上最右的节点
    if(node->left!=nullptr) return getRightMost(node->left);
    else//如果没有左子树，那么就向上找，找到某个节点是其父亲节点的右孩子，其父节点就是前驱节点
    {
        TreeNode *parent = node->parent;
        while(parent!=nullptr && parent->right!=node)
        {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
}

TreeNode* getRightMost(TreeNode *head) //找到左子树上最右的节点
{
    if(head==nullptr) return head;
    TreeNode *cur = head;
    while(cur->right!=nullptr)
    {
        cur = cur->right;
    }
    return cur;
}
TreeNode* getLeftMost(TreeNode *head)
{
    if(head==nullptr) return head;
    TreeNode *cur = head;
    while(cur->left!=nullptr)
    {
        cur = cur->left;
    }
    return cur;
}
