#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

struct ReturnType{
    bool isB;
    int h;
    ReturnType(bool x, int y): isB(x), h(y){}
};

class Solution{
public:
    bool isBalance(TreeNode *root)
    {
        return process(root).isB;
    }

    ReturnType process(TreeNode *root)
    {
        if(root==nullptr)
        {
            ReturnType res(true, 0);
            return res;
        }
        ReturnType fromLeft = process(root->left);
        ReturnType fromRight = process(root->right);
        if(fromLeft.isB && fromRight.isB && abs(fromLeft.h-fromRight.h)<=1)
        {
            ReturnType res(true, max(fromLeft.h, fromRight.h)+1);
            return res;
        }
        ReturnType res(false, max(fromLeft.h, fromRight.h)+1);
        return res;
    }
};

int main()
{
    TreeNode A1(1);
    TreeNode A2(2);
    TreeNode A3(3);
    A1.left = &A2;
    A2.right = &A3;
    Solution s;
    bool res = s.isBalance(&A1);
    cout << res << endl;
    return 0;
}
