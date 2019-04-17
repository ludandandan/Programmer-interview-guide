## 二叉树的先序，中序和后序遍历
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/PreInPosTraversing.cpp)

**题目：**
> 实现二叉树的先序，中序和后序遍历，包括递归方式和非递归方式。

> 遍历顺序：二叉树的先序遍历：中左右；二叉树的中序遍历：左中右；二叉树的后序遍历：左右中。
> 
> 包括递归方法和非递归方法。
> 
> 对于递归方法：递归的终止条件为到某个节点为空则停（返回）。在递归中，一个节点会到达三次，对于一棵由[1,2,3,4,5,6,7]构成的满二叉树，到达每个节点的顺序为：1,2,4,4,4,2,5,5,5,2,1,3,6,6,6,3,7,7,7,3,1。若在第一次到达该节点时打印则是先序遍历[1,2,4,5,3,6,7]；若在第二次到达该节点时打印则是中序遍历[4,2,5,1,6,3,7]；若在第三次到达该节点时打印则是后序遍历[4,5,2,6,7,3,1]。
```c++
void PreOrderRecur(TreeNode *root)
{
    if(root==nullptr) return;
    cout << root->val << ",";
    PreOrderRecur(root->left);
    PreOrderRecur(root->right);
}

void InOrderRecur(TreeNode *root)
{
    if(root==nullptr) return;
    InOrderRecur(root->left);
    cout << root->val << ",";
    InOrderRecur(root->right);
}

void PosOrderRecur(TreeNode *root)
{
    if(root==nullptr) return;
    PosOrderRecur(root->left);
    PosOrderRecur(root->right);
    cout << root->val << ",";
}
```

> 对于非递归的方法。由于二叉树的结构只能从上到下，遍历又需要从底层到上层，这时就用到了栈结构。
> 1. 先序遍历：要按照中左右遍历。先压入中间节点，弹出，若右节点不为空先压右，左节点不为空再压左，这样弹出时左节点就比右节点早弹出。注意一开始先将根节点压栈后再进入while循环，直到栈为空停。
> 2. 中序遍历：要按照左中右的顺序遍历。一下先把当前节点及其左边界全部压栈，然后再慢慢弹出来。当前节点若不为空，将当前节点压栈，同时当前节点往其左边跑；当前节点若为空，从栈中弹出一个节点做完当前节点，当前节点往其右边跑。注意中序的根节点一开始并不进栈，进了while循环后才进栈，while循环的条件有两个满足一个即可（栈不为空或当前节点不为空）
> 3. 后序遍历：要按照左右中的顺序遍历。实际上可看做是堆中右左的逆序。按照先序遍历的方法，只是先压左后压右。
```c++
void PreOrder(TreeNode *root)
{
    if(root==nullptr) return;
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty())
    {
        TreeNode *cur = s.top();
        s.pop();
        cout << cur->val << ",";
        if(cur->right!=nullptr) s.push(cur->right);
        if(cur->left!=nullptr) s.push(cur->left);
    }
}

void InOrder(TreeNode *root)
{
    if(root==nullptr) return;
    stack<TreeNode*> s;
    TreeNode *cur = root;
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
            cout << cur->val << ",";
            cur = cur->right;
        }
    }
}

void PosOrder(TreeNode *root)
{
    if(root==nullptr) return;
    stack<TreeNode*> s1, s2;
    s1.push(root);
    while(!s1.empty())
    {
        TreeNode *cur = s1.top();
        s1.pop();
        s2.push(cur);
        if(cur->left!=nullptr) s1.push(cur->left);
        if(cur->right!=nullptr) s1.push(cur->right);
    }
    while(!s2.empty())
    {
        TreeNode *cur = s2.top();
        s2.pop();
        cout << cur->val << ",";
    }
}
```