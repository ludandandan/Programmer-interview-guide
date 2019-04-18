## 判断是否为搜索二叉树
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isBST.cpp)
**题目：**
> 给定一棵树的根节点，判断这棵树是否树搜索二叉树。搜索二叉树需满足对任意一个节点，其左子树上的节点都比它小，其右子树上的节点都比它大。

> 二叉树的中序遍历如果是升序的那么这棵树就是搜索二叉树。

```c++
bool isBST(TreeNode *root)
{
    if(root==nullptr) return true;
    stack<TreeNode*> s;
    TreeNode *cur = root;
    int pre = INT_MIN;
    while(!s.empty() || cur!=nullptr)
    {
        if(cur!=nullptr)
        {
            s.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = s.top();
            s.pop();
            if(cur->val < pre) return false;
            pre = cur->val;
            cur = cur->right;
        }
    }
    return true;
}

```