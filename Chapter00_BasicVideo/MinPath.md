## 最小路径问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/minPath.cpp)

**题目：**
> 给定一个二维数组matrix，二维数组中的每个数都是正数。要求从左上角到右下角，每步只能向下或者向右。沿途的数字要累加起来，返回最小路径和。

> 方法一： 暴力递归
>  定义一个函数walk(vector<vector<int>> matrix, int i, int j)表示从(i,j)位置到最右下角的最小路径和。所要求的最终结果为walk(matrix, 0, 0)。先确定base case。首先若(i,j)已经到达了矩阵的最右下角，那么最小路径和就是最右下角的值。若是在最后一行，那么就只能向右走，那么当前点(i,j)的最小路径和就是当前矩阵的值加上它右边的点的最小路径和。若是在最后一列，那么就只能向下走，当前点(i,j)的最小路径和就是当前矩阵的值加上它下边点的最小路径和。若是在普遍位置，那么就需要先看看它右边的最小路径和和它下边的最小路径和哪个较小，由较小的那个加上当前的矩阵值就是当前点的最小路径和。

```c++
int minPath(vector<vector<int>> matrix)
{
    return walk(matrix, 0, 0);
}
int walk(vector<vector<int>> matrix, int i, int j)
{
    // 从(i,j)位置开始到最右下角的最小路径和
    //当已经到达最右下角了
    if(i==matrix.size()-1 && j==matrix[0].size()-1) return matrix[i][j];
    //如果在最后一行
    if(i==matrix.size()-1)
    {
        return matrix[i][j]+walk(matrix, i, j+1);
    }
    //如果在最后一列只能向下
    if(j==matrix[0].size()-1)
    {
        return matrix[i][j]+walk(matrix, i+1, j);
    }

    int right = matrix[i][j] + walk(matrix, i, j+1);
    int down = matrix[i][j] + walk(matrix, i+1, j);
    return min(right, down);
}
```
> 暴力递归的时间复杂度分析。要求的值是f(0,0),它依赖它的右边和下边的值f(0,1)和f(1,0)，然后f(0,1)又依赖f(1,1)和f(0,1)；f(1,0)依赖f(1,1)和f(2,0)。这样就相当于一棵树，高度为M+N（matrix行数为M，列数为N），树的节点数就是要计算的f个数，是一颗完全二叉树，节点个数为$2^{M+N}-1$个，故时间复杂度为$O(2^{M+N})$。可是这个树中有好多节点是重复计算的，如f(1,1)。不管是从(0,1)到(1,1)还是从(1,0)到(1,1)对f(1,1)来说计算都一样。
> 
> 对于递归展开后有重复状态，并且这个状态与到达它的路径无关（即无后效性）的递归问题可以转换为动态规划。
> 
> 暴力递归转动态规划的过程：
> 1. 写出暴力递归版本
> 2. 分析可变参数。哪几个可变参数可以代表返回值的状态（对于这个题来说就是i和j），可变参数是n维的那么就建一张n维的dp表。（本题是二维的，并且i的范围为[0, M-1],j的范围为[0, N-1]）
> 3. 确定所需要的最终状态，在表中标记出来（在心里记着就行，最后返回这个值）
> 4. 回到递归版本的base case中把不依赖其他位置的状态都在dp表中设置好
> 5. 通过一个普遍位置，看看它需要哪些位置。那么逆着回去就是填表的顺序。

```c++
int minPathDp(vector<vector<int>> matrix)
{
    return process(matrix);
}
int process(vector<vector<int>> matrix)
{
    int row = matrix.size();
    int col = matrix[0].size();
    vector<vector<int>> dp(row, vector<int>(col));
    for(int i=0; i<row; i++)
    {   
        for(int j=0; j<col; j++)
        {
            dp[i][j] = INT_MAX;
        }
    }

    // dp[i][j]表示从(i,j)位置到最有右下角的最小路径和
    // 对最右下角的数
    dp[row-1][col-1] = matrix[row-1][col-1];
    // 对最后一行
    for(int j=col-2; j>=0; j--)
    {
        dp[row-1][j] = matrix[row-1][j] + dp[row-1][j+1];
    }
    // 对最后一列
    for(int i=row-2; i>=0; i--)
    {
        dp[i][col-1] = matrix[i][col-1] + dp[i+1][col-1];
    }

    //对其他普遍位置
    for(int i=row-2; i>=0; i--)
    {
        for(int j=col-2; j>=0; j--)
        {
            dp[i][j] = min(dp[i+1][j],dp[i][j+1])+matrix[i][j];
        }
    }
    return dp[0][0];
}
```