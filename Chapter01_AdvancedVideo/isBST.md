# 判断一棵树是否为搜索二叉树
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/isBST.cpp)

**题目：**

给定二叉树的一个头节点head，已知其中没有重复值的节点，实现一个函数判断这棵二叉树是否是搜索二叉树。

**解析：**

搜索二叉树的中序遍历是升序的，改写中序遍历，发现是降序的，那么这棵树就不是搜索二叉树。使用Moris中序遍历，可以实现时间复杂度O(N)，空间复杂度O(1)。

但是， Moris遍历分调整二叉树结构和恢复二叉树结构两个阶段。因此，当发现节点值是降序时，不能直接返回false，因为这样可能会跳过恢复阶段，从而破坏二叉树的结构。

```c++
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
```
