## 求一棵完全二叉树的节点个数
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/nodeNum.cpp)

**题目：**
> 给定一棵完全二叉树的头部，请求其节点个数。若节点个数为N，请做到时间复杂度小于O(N)。
> 
> 对于一棵有l层的满二叉树，其节点个数为$2^{l}-1$个。完全二叉树是满二叉树的扩展，可以用这个公式加速计算完全二叉树的节点数。
> 1. 先遍历一下完全二叉树的左边界，记录这棵树的总高度h。这个h在以下的计算中不变化了。
> 2. 然后遍历这棵树根节点x(层数level=1)的右子树的左边界（可以用1的函数得到x右子树的高度hl，若h-level==hl，说明右子树的左边界到了h），若右子树的左边界到了h，说明x的左子树是满二叉树，此时左子树的高度为hl，计算左子树的节点个数$2^{hl}-1$，再加上当前节点x，那么它的节点个数为$2^{l}$。用同样的方法递归得到右子树的节点数。x变为x->right，level+1，但是h不变，递归的终止条件是level==h，也就是到了叶节点时，高度确定为1返回1。
> 3. 若右子树的左边界没有到h，那么x的右子树是满的，并且右子树的高度为hl，计算右子树的节点个数$2^{hl}-1$，再加上当前节点x，那么它的节点个数为$2^{l}$。再用同样的方法得到左子树的节点数。x变为x->left，level+1，但是h不变，递归的终止条件是level==h，也就是到了叶节点时，高度确定为1返回1。

```c++
int nodeNum(TreeNode *root)
{
    if(root==nullptr) return 0;
    int h = getTreeHeight(root); //获得整棵树的总高度
    return getNodeNum(root, 1, h);
}

//获得以root为根的树的高度
int getTreeHeight(TreeNode *root)
{
    if(root==nullptr) return 0;
    int res = 0;
    TreeNode *cur = root;
    while(cur!=nullptr)
    {
        res++;
        cur = cur->left;
    }
    return res;
}

//获得以Node为头节点的树的节点个数
int getNodeNum(TreeNode *node, int level, int h)
{
    //base case: 叶节点的树高度为1
    if(level==h) return 1;
    int hl = getTreeHeight(node->right);//右子树的高度
    if(hl==h-level)//若右子树的左边界到了h，那么左子树就是满的
    {
        int lNum = 1<<hl;//当右子树的边界到h时，右子树的高度和左子树高度一致
        int rNum = getNodeNum(node->right, level+1, h);
        return lNum+rNum;
    }
    else //否则右子树是满的
    {
        int rNum = 1<<hl;
        int lNum = getNodeNum(node->left, level+1, h);
        return rNum+lNum;
    }

}
```