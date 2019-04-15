#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

void spiralOrderPrint(vector<vector<int>>& matrix);
void printEdge(vector<vector<int>> &matrix, int tx, int ty, int dx, int dy);
int main()
{
    vector<vector<int>> matrix{{1,2,3,4},{5,6,7,8}};
    spiralOrderPrint(matrix);
    return 0;
}

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
