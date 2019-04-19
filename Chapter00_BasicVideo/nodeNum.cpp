#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x), left(nullptr), right(nullptr){}
};

int nodeNum(TreeNode *root);
int getTreeHeight(TreeNode *root);
int getNodeNum(TreeNode *node, int level, int h);

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
    //A3.right = &A7;
    //A4.left = &A8;
    //A4.right = &A9;
    //A5.left = &A10;
    //A5.right = &A11;

    int res = nodeNum(&A1);
    cout << res << endl;
    return 0;
}

int nodeNum(TreeNode *root)
{
    if(root==nullptr) return 0;
    int h = getTreeHeight(root); //获得整棵树的总高度
    return getNodeNum(root, 1, h);
}

//获得以root为根的树的高度
int getTreeHeight(TreeNode *root)
{
    if(root==nullptr) return 0;
    int res = 0;
    TreeNode *cur = root;
    while(cur!=nullptr)
    {
        res++;
        cur = cur->left;
    }
    return res;
}

//获得以Node为头节点的树的节点个数
int getNodeNum(TreeNode *node, int level, int h)
{
    //base case: 叶节点的树高度为1
    if(level==h) return 1;
    int hl = getTreeHeight(node->right);//右子树的高度
    if(hl==h-level)//若右子树的左边界到了h，那么左子树就是满的
    {
        int lNum = 1<<hl;//当右子树的边界到h时，右子树的高度和左子树高度一致
        int rNum = getNodeNum(node->right, level+1, h);
        return lNum+rNum;
    }
    else //否则右子树是满的
    {
        int rNum = 1<<hl;
        int lNum = getNodeNum(node->left, level+1, h);
        return rNum+lNum;
    }

}
