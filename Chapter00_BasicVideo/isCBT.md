## 判断一棵树是否是完全二叉树
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isCBT.cpp)

**题目：**
> 给定一棵树的根节点，判断这棵树是否是完全二叉树。

> 对二叉树采用按层遍历的方式遍历每个节点，看其是否满足以下条件：
> 1. 若一个节点，它有右子树而没有左子树，那么它一定不是完全二叉树。返回false。
> 2. 若一个节点，它不是两个孩子都有（有左没右，或左右都没有，对于没中1的就是没有右），那么开启一个阶段，这阶段开启后，从现在开始遍历到的节点必须是叶节点，否则就不是完全二叉树，返回false。
> 3. 若对所以节点遍历完后1，2都满足，没有返回false，那么这棵树就是完全二叉树。

```c++
//按层遍历，只需要一个队列就可以了，把每一层放到一个vector<int>中，
//把整棵树放到vector<vector<int>>中需要两个队列交替使用
void levelTraversal(TreeNode *root)
{
    if(root==nullptr) return;
    queue<TreeNode*> q;
    TreeNode *cur = root;
    q.push(cur);
    while(!q.empty())
    {
        cur = q.front();
        q.pop();
        cout << cur->val << " ";
        if(cur->left) q.push(cur->left);
        if(cur->right) q.push(cur->right);
    }
}

bool isCBT(TreeNode *root)
{
    if(root==nullptr) return true;
    queue<TreeNode*> q;
    bool leaf = false;
    TreeNode *cur = root;
    q.push(cur);
    while(!q.empty())
    {
        cur = q.front();
        q.pop();
        //如果没有左孩子有右孩子则返回false
        if(cur->left==nullptr && cur->right!=nullptr) return false;
        //如果开启了那个阶段(两个孩子不是都全)后，不是叶节点就返回false
        if(leaf && (cur->left!=nullptr || cur->right!=nullptr)) return false;
        if(cur->left!=nullptr) q.push(cur->left);
        if(cur->right!=nullptr) q.push(cur->right);
        else //有左没右，左右都没有，两个孩子不是都全
        {
            leaf = true;
        }
    }
    return true;
}

```