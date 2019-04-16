#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

bool isContainsInMatrix(vector<vector<int>> &matrix, int k);

int main()
{
    //输入逗号分隔的矩阵
    vector<vector<int>> matrix;
    string line;
    while(getline(cin, line))
    {
        vector<int> arr;
        istringstream is(line);
        int n;
        char ch;
        while(is>>n)
        {
            arr.push_back(n);
            is>>ch;
        }
        matrix.push_back(arr);
    }

    bool res = isContainsInMatrix(matrix, 8);
    cout << res << endl;
    return 0;
}

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

