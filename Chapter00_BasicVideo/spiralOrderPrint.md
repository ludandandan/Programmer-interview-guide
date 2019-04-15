## 转圈打印矩阵
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/spiralOrderPrint.cpp)

**题目：**
>   给定一个整型矩阵matrix，请按照转圈的方式打印它。额外空间复杂度O(1)。

> 将这个问题划分为小问题，先定义一个函数，给定矩阵的左上角点坐标和右下角点坐标，打印由这两个点构成的矩阵的边界。有了这个函数之后，只需向中间移动左上角和右下角的点就可以打印整个矩阵类。
> 
> 假设给定左上角坐标(a,b)，右下角坐标(c,d)。注意打印边界时的顺序，先打印上面的行a++到c， 再打印右边的列b++到d， 再打印下面的行c--到a，再打印左边的列d--到b。注意前面到x，但并不能等于x，这样才能循环起来不重复打印。在打印边界时还有两种特殊情况，一是左上角点和右下角点在同一行，即b==d,此时只需将a++到c即可，此时到c需要等于c；二是左上角点和右下角点在同一列，即a==c,此时只需将b++到d即可，此时到d需等于d。

> 在总的函数中，向右下角调整左上角点坐标(a++,b++)，向左上角调整右下角点坐标(c--,d--)，但不要使两者错过。当左上角的行或列大于等于右下角的行或列时停。

```c++
void printEdge(vector<vector<int>> &matrix, int tx, int ty, int dx, int dy)
{//x对应col,y对应row
    if(tx==dx) //在同一列
    {
        for(int i=ty; i<=dy; i++) cout << matrix[i][tx] << " ";
    }
    else if(ty==dy) //在同一行
    {
        for(int i=tx; i<=dx; i++) cout << matrix[ty][i] << " ";
    }
    else
    {
        int curx = tx;
        int cury = ty;
        while(curx != dx)
        {
            cout << matrix[ty][curx] << " ";
            curx++;
        }
        while(cury != dy)
        {
            cout << matrix[cury][dx] << " ";
            cury++;
        }
        while(curx != tx)
        {
            cout << matrix[dy][curx] << " ";
            curx--;
        }
        while(cury != ty)
        {
            cout << matrix[cury][tx] << " ";
            cury--;
        }
    }
}

void spiralOrderPrint(vector<vector<int>> &matrix)
{
    if(matrix.empty() || matrix[0].empty()) return;
    int tx = 0;
    int ty = 0;
    int dy = matrix.size()-1;
    int dx = matrix[0].size()-1;
    while(tx<=dx && ty<=dy)
    {
        printEdge(matrix, tx++, ty++, dx--, dy--);
        
    }
}

```