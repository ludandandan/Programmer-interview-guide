#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void rotateMatrix(vector<vector<int>> &matrix);
void rotate(vector<vector<int>> &matrix, int tr, int tc, int dr, int dc);
void rotateMatrix2(vector<vector<int>> &matrix);
int main()
{
    vector<vector<int>> matrix{{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    vector<vector<int>> matrix1 = matrix;
    vector<vector<int>> matrix2 = matrix;
    for(auto w:matrix)
    {
        for(auto m: w)
        {
            cout << m << " ";
        }
        cout << endl;
    }
    rotateMatrix(matrix1);
    for(auto w: matrix1)
    {
        for(auto m:w)
        {
            cout << m << " ";
        }
        cout << endl;
    }
    rotateMatrix2(matrix2);
    for(auto w: matrix2)
    {
        for(auto m: w)
        {
            cout << m << " ";
        }
        cout << endl;
    }
    return 0;
}

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
