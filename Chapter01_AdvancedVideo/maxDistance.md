# 二叉树节点间的最大距离问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/maxDistance.cpp)

**题目：**

从二叉树的节点A出发，可以向上走，也可以向下走，但沿途的节点只能经过一次，当到达节点B时，路径上的节点数叫做A到B的距离。

比如，二叉树
```c++
A1.left = &A2;
A1.right = &A3;
A2.left = &A4;
A2.right = &A5;
A3.left = &A6;
A3.right = &A7
```
这棵树中，节点2到节点4的距离为2节点5到节点6之间的距离为5.

**要求：**

如果二叉树的节点数为N,时间复杂度O(N)

**解析：**

分析可能性：
1. 最大距离可能来自左子树
2. 最大距离可能来自右子树
3. 最大距离可能是左子树的深度+根节点+右子树的深度

从这三种结果中取最大值

那么设计返回的结构。
1. 这棵树的深度
2. 这棵树上的最大距离

一棵树的深度就是max(左子树的深度，右子树的深度)+1


```c++
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

struct ReturnType{
    int h;//深度
    int maxD; //最大距离
    ReturnType(int x, int y): h(x), maxD(y){}
};

class Solution{
public:
    int maxDistance(TreeNode *root)
    {
        return process(root).maxD;
    }

    ReturnType process(TreeNode *root)
    {
        //若是根为空，那么深度为0，最大距离为0
        if(root==nullptr)
        {
            ReturnType res(0,0);
            return res;
        }
        //从左树收集信息
        ReturnType fromLeft = process(root->left);
        //从右树收集信息
        ReturnType fromRight = process(root->right);
        int h = max(fromLeft.h, fromRight.h)+1;
        int maxD = max(max(fromLeft.maxD, fromRight.maxD), fromLeft.h+fromRight.h+1);
        ReturnType res(h, maxD);
        return res;
    }
```