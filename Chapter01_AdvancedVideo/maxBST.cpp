#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define INT_MIN -65535
#define INT_MAX 65535
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

struct ReturnType{
    int size; //搜索二叉树的大小
    TreeNode *head; //搜索二叉树的头部
    int max; //这棵树中的最大值
    int min; //这棵树的最小值
    ReturnType(int x, TreeNode *y, int z, int m): size(x), head(y), max(z), min(m){}
};

class Solution{
public:
    TreeNode *maxBST(TreeNode *root)
    {
        if(root==nullptr) return nullptr;
        return process(root).head;
    }

    ReturnType process(TreeNode *root)
    {
        if(root==nullptr)
        {
            ReturnType res(0, nullptr, INT_MIN, INT_MAX);
            return res;
        }

        //从左子树上收集信息
        ReturnType fromLeft = process(root->left);
        //从右子树上收集信息
        ReturnType fromRight = process(root->right);
        int minval = min(min(fromLeft.min, fromRight.min), root->val);
        int maxval = max(max(fromLeft.max, fromRight.max), root->val);
        int size = max(fromLeft.size, fromRight.size); //先只考虑最大搜索二叉树来自左树或者右树
        TreeNode *head = fromLeft.size>fromRight.size? fromLeft.head: fromRight.head;
        //若是左子树是搜索二叉树并且右子树也是搜索二叉树并且左子树上最大值比root小《右子树上最小值比root大
        //那么整棵树都是搜索二叉树
        if(fromLeft.head==root->left && fromRight.head==root->right && fromLeft.max<root->val && fromRight.min>root->val)
        {
            size = fromLeft.size + fromRight.size + 1;
            head = root;
        }
        ReturnType res(size, head, maxval, minval);
        return res;
    }
};

int main()
{
    TreeNode A6(6);
    TreeNode A1(1);
    TreeNode A12(12);
    TreeNode A0(0);
    TreeNode A3(3);
    TreeNode A10(10);
    TreeNode A13(13);
    TreeNode A4(4);
    TreeNode A14(14);
    TreeNode A20(20);
    TreeNode A16(16);
    TreeNode A2(2);
    TreeNode A5(5);
    TreeNode A11(11);
    TreeNode A15(15);

    Solution s;
    A6.left = &A1;
    A6.right = &A12;
    A1.left = &A0;
    A1.right = &A3;
    A12.left = &A10;
    A12.right = &A13;
    A10.left = &A4;
    A10.right = &A14;
    A13.left = &A20;
    A13.right = &A16;
    A4.left = &A2;
    A4.right = &A5;
    A14.left = &A11;
    A14.right = &A15;
    TreeNode *root = s.maxBST(&A6);
    cout << root->val << endl;
    return 0;
}
