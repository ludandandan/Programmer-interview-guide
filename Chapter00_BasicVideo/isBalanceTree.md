## 判断一棵二叉树是否为平衡二叉树
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isBalanceTree.cpp)

**题目：**
>平衡二叉树的性质为：要么是一棵空树，要么任何一个节点的左右子树高度差的绝对值不超过1。给定一棵二叉树的根节点root，判断这棵二叉树是否是平衡二叉树。

> 判断一棵树是否为平衡二叉树：如果以每个点作为头节点的树都是平衡二叉树，那么这棵树才是平衡二叉树。
> 
> 那么如何判断以x为根节点的树是否是平衡二叉树?
> 1. x的左子树是平衡的
> 2. x的右子树是平衡的
> 3. 左子树的高度与右子树的高度差不超过1。
> 
> 可以用递归的方式解决这道题目。对二叉树的递归，可以到达每个节点三次：第一次来到这个节点，在它左子树绕一圈再回到这个节点，在它右子树绕一圈再回到这个节点。故可以收集这个节点的左子树信息和右子树信息，然后再进行整合来判断以这个节点为根的树是否平衡。
> 这里需要记录左右子树是否平衡和左右子树的高度，若左或右子树不平衡，那么其高度也就不重要了，所以可以用高度等于-1来标记左右子树不平衡，只要不是-1就是平衡。
> 先获得左子树的信息，若不平衡直接返回-1，左子树不平衡那整棵树必不平衡。再获得右子树的信息，若不平衡直接返回-1。若左右子树都平衡那么再计算高度差，若高度差大于1直接返回-1。若高度差不大于-1，那么需要返回这棵树的高度。
```c++
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
```