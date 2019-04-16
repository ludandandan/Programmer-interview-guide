## 在行和列都排好序的矩阵中找数
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isContainsInMatrix.cpp)

**题目：**
> 给定一个N*M的整型矩阵matrix和一个整数K，matrix的每一行和每一列都是排好序的。实现一个函数，判断K是否在matrix中。
> 
> 要求时间复杂度O(N+M)，额外空间复杂度O(1)。
> 例如矩阵{{1,3,5,6},{2,5,7,9},{4,6,8,10}}
> 
> 有两个路线可以考虑：
>  1. 从矩阵的右上角m[i][j]=m[0][M-1]开始查找，若发现m[i][j]的值比k大，那么它右边的数都没戏了，这个点向下走i++,若m[i][j]比k小，那么它下面的点都没戏了，这个点向左走j--，若发现相等了返回true，若是越界了也没找到相等就返回false。
> 2. 与1同理。从矩阵的左下角开始找，若是这个点比k大了就往上走，否则就往右走。
> 3. 为什么旋转右上角或左下角，而不是左上角或右下角？因为左上角的右边和下面都是比它大的，同样右下角的上面和左边都是比它小的，不能同时兼顾或大或小两种情况。

```c++

bool isContainsInMatrix(vector<vector<int>> &matrix, int k)
{
    if(matrix.empty() || matrix[0].empty()) return false;
    int r = matrix.size();
    int c = matrix[0].size();
    // from right top
    int xr = 0;
    int xc = c-1;
    while(xr<r && xc>=0)
    {
        if(matrix[xr][xc]==k) return true;
        else if(matrix[xr][xc]<k) xr++;
        else xc--;
    }
    return false;
}
```