#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

class Solution{
public:
    bool isCBT(TreeNode *root)
    {
        //按层遍历，就需要用到队列
        if(root==nullptr) return true;
        queue<TreeNode*> q;
        TreeNode *cur = root;
        q.push(cur);
        bool flag = false; //若是不是两个孩子双全，那么从这这之后都必须是叶子节点
        while(!q.empty())
        {
            cur = q.front();
            q.pop();
            if(cur->left!=nullptr) q.push(cur->left);
            if(cur->right!=nullptr) q.push(cur->right);
            //若是有右无左就返回false
            if(cur->right!=nullptr && cur->left==nullptr) return false;
            //若是开启了那个叶子节点阶段,然后发现并不是叶子节点， 返回false
            if(flag && (cur->left!=nullptr || cur->right!=nullptr)) return false;
            //若是不是两个孩子双全
            if(!flag && (cur->left==nullptr || cur->right==nullptr)) flag = true;
        }
        return true;
    }
};

int main()
{
    TreeNode A1(1);
    TreeNode A2(2);
    TreeNode A3(3);
    TreeNode A4(4);
    TreeNode A5(5);
    A1.left = &A2;
    A1.right = &A3;
    A2.left = &A4;
    A2.right = &A5;

    Solution s;
    bool res = s.isCBT(&A1);
    cout << res << endl;
    return 0;
}
