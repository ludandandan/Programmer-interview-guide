#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution{
public:
    int win(vector<int> arr)
    {
        if(arr.empty() || arr.size()==0) return 0;
        return max(f(arr, 0, arr.size()-1), s(arr, 0, arr.size()-1));
    }

    //让绝顶聪明的人先拿，那么他会得到多少分
    int f(vector<int> &arr, int i, int j)
    {
        if(i==j) return arr[i];
        return max(arr[i]+s(arr, i+1, j), s(arr, i, j-1)+arr[j]);
    }

    //让绝顶聪明的人后拿，那么他会得到多少分
    int s(vector<int> &arr, int i, int j)
    {
        if(i==j) return 0;
        return min(f(arr, i+1, j), f(arr, i, j-1));
    }

    int winDp(vector<int> arr)
    {
        if(arr.empty() || arr.size()==0) return 0;
        int n = arr.size();
        //建两张dp表，一个f，一个s
        vector<vector<int>> dpf(n, vector<int>(n));
        vector<vector<int>> dps(n, vector<int>(n));
        for(int i=0; i<n; i++) 
        {
            dpf[i][i] = arr[i];
            dps[i][i] = 0;
        }
        for(int j=1; j<n; j++)
        {
            for(int i=j-1; i>=0; i--)
            {
                dpf[i][j] = max(arr[i]+dps[i+1][j], arr[j]+dps[i][j-1]);
                dps[i][j] = min(dpf[i+1][j], dpf[i][j-1]);
            }
        }
        return max(dpf[0][n-1], dps[0][n-1]);
    }
};


int main()
{
    vector<int> arr{1, 2, 100, 4};
    Solution s;
    int res = s.win(arr);
    cout << res << endl;
    int res2 = s.winDp(arr);
    cout << res2 << endl;
    return 0;
}
