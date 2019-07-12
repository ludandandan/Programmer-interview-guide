# 判断二叉树是否为平衡二叉树
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/isBalance.cpp)

**题目：**

平衡二叉树的性质为：要么是一棵空树，要么任何一个节点的左右子树高度差的绝对值不超过1.给定一棵二叉树的头节点head，判断这棵二叉树是否是平衡二叉树。

**要求：**

如果二叉树的节点数为N，则要求时间复杂度为O(N)

**解答：**

依次考察以每个节点为头的子树，如果都是平衡二叉树，那么整体就是平衡二叉树。
树形dp的套路。以某个节点x为头，分析有哪些可能性
1. 若x的左子树不是平衡的，那么以x为头节点的树是不平衡的
2. 若x的右子树不是平衡的，那么以x为头节点的树是不平衡的
3. 若x的左子树是平衡的，右子树也是平衡的，左子树与右子树的高度差大于1，那么以x为头节点的树是不平衡
4. 若是上面3种都不中，那么这棵树就是平衡的
   
构建返回结构：
1. 是否是平衡的
2. 树的高度

```c++
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
```