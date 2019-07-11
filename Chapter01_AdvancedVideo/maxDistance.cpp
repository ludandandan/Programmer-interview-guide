#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

struct ReturnType{
    int h;//深度
    int maxD; //最大距离
    ReturnType(int x, int y): h(x), maxD(y){}
};

class Solution{
public:
    int maxDistance(TreeNode *root)
    {
        return process(root).maxD;
    }

    ReturnType process(TreeNode *root)
    {
        //若是根为空，那么深度为0，最大距离为0
        if(root==nullptr)
        {
            ReturnType res(0,0);
            return res;
        }
        //从左树收集信息
        ReturnType fromLeft = process(root->left);
        //从右树收集信息
        ReturnType fromRight = process(root->right);
        int h = max(fromLeft.h, fromRight.h)+1;
        int maxD = max(max(fromLeft.maxD, fromRight.maxD), fromLeft.h+fromRight.h+1);
        ReturnType res(h, maxD);
        return res;
    }
};

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

    Solution s;
    int res = s.maxDistance(&A1);
    cout << res << endl;
    return 0;
}
