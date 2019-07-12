# 判断一棵二叉树是否完全二叉树

**题目：**

给定二叉树的一个头节点head，已知其中没有重复值的节点，判断这棵二叉树是否为完全二叉树

**解析：**

对二叉树进行按层遍历，从左向右遍历所有节点：
1. 若是当前节点有右孩子，没有左孩子，则直接返回false
2. 若是当前节点不是左右孩子双全，那么从这之后（开启了一个新的阶段）的所有节点都必须是叶子节点，否则返回false
3. 若是遍历结束了，还没返回false，那么返回true

```c++
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
```