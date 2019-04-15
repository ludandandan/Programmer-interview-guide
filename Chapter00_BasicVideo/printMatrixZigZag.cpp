#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

void printMatrixZigZag(vector<vector<int>> &matrix);
void printZigZag(vector<vector<int>> &matrix, int aR, int aC, int bR, int bC, bool fromUp);

int main()
{
    vector<vector<int>> matrix{{1,2,3,4},{5,6,7,8},{9,10,11,12}};

    for(auto w: matrix)
    {   
        for(auto m: w)
        {
            cout << m << " ";
        }
        cout << endl;
    }
    printMatrixZigZag(matrix);
}

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
       // bR = bR==(R-1)? bR: bR+1;
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
