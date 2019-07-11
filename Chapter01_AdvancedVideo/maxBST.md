# 求最大搜索二叉树的大小
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/maxBST.cpp)

**题目：**

给定一棵二叉树的头节点head，已知其中所有节点的值都不一样，找到含有节点最多的搜索二叉树，并返回这棵树的头节点。

**要求：**

如果节点数为N，则要求时间复杂度为O(N)，额外空间复杂度为O(h)， h 为二叉树的高度

**解析：**

搜索二叉树要求，它左子树上的数都比头小，右子树上的数都比头大。

树形dp，二叉树的套路：从左子树上收集信息，从右子树上收集信息，然后组合成自己的信息，返回父亲。

先列可能性：
    1. 最大搜索二叉树可能来自它的左子树
    2. 最大搜索二叉树可能来自它的右子树
    3. 最大搜索二叉树可能是它本身

这里需要收集的信息有

    1. 左子树上最大搜索二叉树的大小（节点个数）；右子树上最大搜索二叉树的大小（节点个数）
    2. 左子树的最大值； 右子树的最小值
    3. 左子树上最大搜索二叉树的头部，右子树上最大搜索二叉树的头部
   
设计要返回的结构体：
  
    1. 最大搜索二叉树的大小（节点个数）
    2. 最大搜索二叉树的头部
    3. 这棵树的最大值和最小值


```c++
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

struct ReturnType{
    int size; //搜索二叉树的大小
    TreeNode *head; //搜索二叉树的头部
    int max; //这棵树中的最大值
    int min; //这棵树的最小值
    ReturnType(int x, TreeNode *y, int z, int m): size(x), head(y), max(z), min(m){}
};

class Solution{
public:
    TreeNode *maxBST(TreeNode *root)
    {
        if(root==nullptr) return nullptr;
        return process(root).head;
    }

    ReturnType process(TreeNode *root)
    {
        if(root==nullptr)
        {
            ReturnType res(0, nullptr, INT_MIN, INT_MAX);
            return res;
        }

        //从左子树上收集信息
        ReturnType fromLeft = process(root->left);
        //从右子树上收集信息
        ReturnType fromRight = process(root->right);
        int minval = min(min(fromLeft.min, fromRight.min), root->val);
        int maxval = max(max(fromLeft.max, fromRight.max), root->val);
        int size = max(fromLeft.size, fromRight.size); //先只考虑最大搜索二叉树来自左树或者右树
        TreeNode *head = fromLeft.size>fromRight.size? fromLeft.head: fromRight.head;
        //若是左子树是搜索二叉树并且右子树也是搜索二叉树并且左子树上最大值比root小《右子树上最小值比root大
        //那么整棵树都是搜索二叉树
        if(fromLeft.head==root->left && fromRight.head==root->right && fromLeft.max<root->val && fromRight.min>root->val)
        {
            size = fromLeft.size + fromRight.size + 1;
            head = root;
        }
        ReturnType res(size, head, maxval, minval);
        return res;
    }
};

```