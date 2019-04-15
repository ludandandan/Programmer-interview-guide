## 将正方形矩阵顺时针转到90度
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/rotateMatrix.cpp)

**题目：**
> 给定一个N*N大小的整型矩阵，将矩阵调整为顺时针转动90度的形式。要求空间复杂度O(1)。

> 方法一：
>  类似转圈打印矩阵的方法，先将整个矩形分为一圈一圈的矩形边框，一个边框一个边框的旋转90度。如果能把一个矩形边框旋转90度那么也就能把整个矩形旋转90度。一个矩形边框的确定只需要左上角点和右下角点，对于一个矩形边框，可以找到旋转时联动的四个点，四个点四个点的调整。知道把矩形边框上面的行里所有点对应的四个点都调整完毕就把整个矩形边框调整完毕列。注意这一行的点不包括最后一个元素，因为它已经包括在第一个元素的四个点里了。

> 方法二：
>   先将整个矩形以副对角线为轴对称交换，然后再以中间一行为轴对称交换就可得到旋转90的矩形。以对角线为轴时元素交换：m(i,j)与m(n-1-j, n-1-i)，其中n为矩阵的边长。

> 方法一：
```c++
void rotateMatrix(vector<vector<int>> &matrix)
{
    if(matrix.empty() || matrix[0].empty()) return;
    int tr = 0;
    int tc = 0;
    int dr = matrix.size()-1;
    int dc = matrix[0].size()-1;
    while(tr<dr)
    {
        rotate(matrix, tr++, tc++, dr--, dc--);
    }
}

void rotate(vector<vector<int>> &matrix, int tr, int tc, int dr, int dc)
{
    for(int i=0; i<dc-tc; i++)
    {
        int tmp = matrix[tr][tc+i];
        matrix[tr][tc+i] = matrix[dr-i][tc];
        matrix[dr-i][tc] = matrix[dr][dc-i];
        matrix[dr][dc-i] = matrix[tr+i][dc];
        matrix[tr+i][dc] = tmp;
    }
}
```

> 方法二：
```c++
void rotateMatrix2(vector<vector<int>> &matrix)
{
    if(matrix.empty() || matrix[0].empty()) return;
    int n = matrix.size();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i; j++)
        {
            swap(matrix[i][j], matrix[n-1-j][n-1-i]);
        }
    }
    for(int i=0; i<n/2; i++)
    {
        for(int j=0; j<n; j++)
        {
            swap(matrix[i][j],matrix[n-i-1][j]);
        }
    }
}

``` 