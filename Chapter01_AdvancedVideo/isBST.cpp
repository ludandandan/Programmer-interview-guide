#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

class Solution{
public:
    bool isBST(TreeNode *root)
    {
        //空树是搜索二叉树
        if(root==nullptr) return true;
        //Moris中序遍历
        TreeNode *cur = root;
        TreeNode *mostRight = nullptr;
        TreeNode *pre = nullptr;
        bool res = true;

        while(cur!=nullptr)
        {
            mostRight = cur->left;
            //若是有左子树。就会到达这个节点两次
            if(mostRight!=nullptr)
            {
                while(mostRight->right!=nullptr && mostRight->right!=cur)
                {
                    mostRight = mostRight->right;
                }
                if(mostRight->right==nullptr)
                {
                    //第一次来到这个节点
                    mostRight->right = cur;
                    cur = cur->left;
                }
                else
                {
                    //第二次来到这个节点，中序遍历便是第二次来到这个节点
                    mostRight->right = nullptr;
                    if(pre!=nullptr && pre->val > cur->val)//若是出现了降序
                    {
                        res = false;
                    }
                    pre = cur;
                    cur = cur->right; //第二次来到这个节点，那么他的左子树就全部遍历过了，向右移动
                }
            }
            else
            {
                //若是没有左子树，第一次和第二次一起
                if(pre!=nullptr && pre->val > cur->val)
                {
                    res = false;
                }
                pre = cur;
                cur = cur->right;
            }
        }
        return res;
    }
};

int main()
{
    TreeNode A7(7);
    TreeNode A4(4);
    TreeNode A10(10);
    TreeNode A3(3);
    TreeNode A6(6);
    TreeNode A8(8);
    TreeNode A11(11);

    A7.left = &A4;
    A7.right = &A10;
    A4.left = &A8;
    Solution s;
    bool res = s.isBST(&A7);
    cout << res << endl;
    return 0;
}
