## 在二叉树中找到一个节点的后继节点，前驱节点
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/getSuccessorNode.cpp)

**题目：**
> 有一种新的二叉树节点类型，比普通的二叉树多了指向父亲节点的指针，如下：
```c++
struct TreeNode{
    int val;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),parent(nullptr),left(nullptr),right(nullptr){}
};
```
> 树的头节点的父亲指针指向空。只给二叉树中的某个节点node，请返回这个节点的后继节点，前驱节点。
> 
> 后继节点：在中序遍历序列中，一个节点的下一个节点就是其后继节点，一棵树的最右边的节点的后继节点为空。
> 
> 前驱节点：在中序遍历序列中，一个节点的前一个节点就是其前驱节点，一棵树的最左边的节点的前驱节点为空。
> 例如，一棵由[1,2,3,4,5,6,7]构成的满二叉树，其中序遍历为：[4,2,5,1,6,3,7]，那么5的后继节点为1，5的前驱节点为2。

> 后继节点求法：
> 
> 中序遍历是按照左中右的顺序遍历的。
> 1. 一个节点x若有右子树，那么它可以看作是“中”，它下一个节点就是其右子树上最左边的节点。
> 2. 一个节点x若没有右子树，那么它可以看作是“左”，它要向上找中，也就是它的父亲，直到找到一个父亲，它是这个父亲的左孩子，那么这个父亲就是它的后继节点。

```c++
TreeNode* getSuccessorNode(TreeNode *node)
{
    if(node==nullptr) return node;
    if(node->right!=nullptr) return getLeftMost(node->right);
    else
    {
        TreeNode *parent = node->parent;
        while(parent!=nullptr && parent->left!=node)
        {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
}

TreeNode* getLeftMost(TreeNode *head)
{
    if(head==nullptr) return head;
    TreeNode *cur = head;
    while(cur->left!=nullptr)
    {
        cur = cur->left;
    }
    return cur;
}
```

> 前驱节点求法：
> 
> 同样是考虑中序遍历的顺序：左中右
> 1. 一个节点如果有左孩子，那么它可看作是“中”，要找的前驱节点就是它左子树上最右边的节点。
> 2. 一个节点如果没有左孩子，那么它可以看作是“右”，它要向上找它的中，也就是它的父亲，直到找到一个父亲，它是这个父亲的右孩子，那么这个父亲就是它的前驱节点。

```c++
TreeNode* getPredecessorNode(TreeNode *node)
{
    if(node==nullptr) return node;
    //如果有左子树，那么前驱节点就是其左子树上最右的节点
    if(node->left!=nullptr) return getRightMost(node->left);
    else//如果没有左子树，那么就向上找，找到某个节点是其父亲节点的右孩子，其父节点就是前驱节点
    {
        TreeNode *parent = node->parent;
        while(parent!=nullptr && parent->right!=node)
        {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
}

TreeNode* getRightMost(TreeNode *head) //找到左子树上最右的节点
{
    if(head==nullptr) return head;
    TreeNode *cur = head;
    while(cur->right!=nullptr)
    {
        cur = cur->right;
    }
    return cur;
}
```