#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
#define INT_MAX 65535
int minPath(vector<vector<int>> matrix);
int walk(vector<vector<int>> matrix, int i, int j);
int minPathDp(vector<vector<int>> matrix);
int process(vector<vector<int>> matrix);

int main()
{
    vector<vector<int>> matrix{
    {3,1,2,0},
    {7,5,0,1},
    {3,7,6,2}
    };
    int res = minPath(matrix);
    cout << res << endl;
    int resdp = minPathDp(matrix);
    cout << resdp << endl;
    return 0;
}

int minPath(vector<vector<int>> matrix)
{
    return walk(matrix, 0, 0);
}

int minPathDp(vector<vector<int>> matrix)
{
    return process(matrix);
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
