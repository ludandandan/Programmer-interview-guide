## 之字形打印矩阵
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/printMatrixZigZag.cpp)

**题目：**
> 给定一个矩阵matrix，要求按照之字形状打印矩阵，额外空间复杂度O(1)。

> 定义两个点A(aR, aC)和B(bR, bC)，一开始都是(0,0)位置，A点一直向右移动，到头了再向下移动，到最后一行停。B点一直向下移动，到头了再向右移动，到最后一列停。定义一个Bool,来确定是从A点打印到B，还是从B到A。注意A，B行列坐标变换的顺序。

```cpp
void printMatrixZigZag(vector<vector<int>> &matrix)
{
    if(matrix.empty() || matrix[0].empty()) return;
    int R = matrix.size();
    int C = matrix[0].size();
    int aR = 0;
    int aC = 0;
    int bR = 0;
    int bC = 0;
    bool fromUp = false;
    while(aR!=R)
    {
        printZigZag(matrix, aR, aC, bR, bC, fromUp);
        aR = aC==(C-1)? aR+1: aR;
        aC = aC==(C-1)? aC: aC+1;
        //bR = bR==(R-1)? bR: bR+1; 错误写法
        bC = bR==(R-1)? bC+1: bC;//先写列，先写不变的，不受三目运算的条件影响的，不然会漏下一些
        bR = bR==(R-1)? bR: bR+1;
        fromUp = !fromUp;
    }
}


void printZigZag(vector<vector<int>> &matrix, int aR, int aC, int bR, int bC, bool fromUp)
{
    if(fromUp)//AtoB
    {
        while(aR<=bR)
        {
            cout << matrix[aR++][aC--] << " ";
        }
    }
    else
    {
        while(bR>=aR)
        {
            cout << matrix[bR--][bC++] << " ";
        }
    }
}
```
