#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct ReturnData{
    bool isB;
    int h;
    ReturnData(bool b, int x): isB(b), h(x){}
};

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

bool isBalance(TreeNode *root);
ReturnData process(TreeNode *root);

bool isBalance1(TreeNode *root);
int getHeight(TreeNode *root);
int main()
{
    TreeNode A1(1);
    TreeNode A2(2);
    TreeNode A3(3);
    TreeNode A4(4);
    TreeNode A5(5);
    TreeNode A6(6);

    A1.left = &A2;
    A1.right = &A3;
    A2.left = &A4;
    A4.left = &A5;

    bool res = isBalance1(&A1);
    cout << res << endl;

    return 0;
}

bool isBalance(TreeNode *root)
{
    return process(root).isB;
}

ReturnData process(TreeNode *root)
{
    ReturnData res(true,0);
    if(root==nullptr)
    {
        res.isB = true;
        res.h = 0;
        return res;
    }

    ReturnData left = process(root->left);
    if(!left.isB) 
    {
        res.isB = false;
        res.h = 0;
        return res;
     }
    ReturnData right = process(root->right);
    if(!right.isB) 
    {
        res.isB = false;
        res.h = 0;
        return res;
    }

    if(abs(left.h-right.h)>1) 
    {
        res.isB = false;
        res.h = 0;
        return res;
     }
    else 
    {
        res.isB = true;
        res.h = max(left.h, right.h)+1;
        return res;
     }
}

bool isBalance1(TreeNode *root)
{
    int res = getHeight(root);
    return res==-1?false:true;
}

int getHeight(TreeNode *root)
{
    if(root==nullptr) return 0;
    int leftH = getHeight(root->left);
    if(leftH==-1) return -1;
    int rightH = getHeight(root->right);
    if(rightH==-1) return -1;
    int c = abs(leftH-rightH);
    if(c>1) return -1;
    else return max(leftH,rightH)+1;
}
