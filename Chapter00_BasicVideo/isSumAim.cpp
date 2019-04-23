#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

bool isSumAim(vector<int> arr, int aim);
bool isSumAim(vector<int> arr, int aim, int i, int sum);
bool isSumAimDp(vector<int> arr, int aim);
int main()
{
    string line; //3,2,7,13
    getline(cin, line);
    istringstream is(line);
    int n;
    char ch;
    vector<int> arr;
    while(is>>n)
    {
        arr.push_back(n);
        is>>ch;
    }
    int aim;
    cin >> aim;
    bool res = isSumAim(arr, aim);
    cout << res << endl;
    cout << "DP: " << endl;
    bool resDp = isSumAim(arr, aim);
    cout << resDp << endl;
    return 0;
}

bool isSumAim(vector<int> arr, int aim)
{
   return isSumAim(arr, aim, 0, 0); 
}

bool isSumAim(vector<int> arr, int aim, int i, int sum)
{
// 之前形成的和为sum，从i位置及它之后的数中任意选择能不能组成aim
//对每个位置的数都有要和不要两种选择
    if(i==arr.size())
    {
        return aim==sum;
    }
    return isSumAim(arr, aim ,i+1, sum+arr[i]) || isSumAim(arr, aim, i+1, sum);
}


bool isSumAimDp(vector<int> arr, int aim)
{
    int S = 0;
    for(int i=0; i<arr.size(); i++)
    {
        S += arr[i];
    }
    if(S<aim) return false;
    int n = arr.size();

    vector<vector<bool>> dp(n+1,vector<bool>(S+1)); // 范围： [0,N], [0,Sum]

    // 对最后一行
    for(int sum=0; sum<=S; sum++)
    {
        if(sum==aim) dp[n][sum] = true;
        else dp[n][sum] = false;
    }

    for(int i=n-1; i>=0; i--)
    {
        for(int sum=0; sum<=S; sum++)
        {
            if(sum+arr[i] <= S)
            {
                dp[i][sum] = (dp[i+1][sum] | dp[i+1][sum+arr[i]]);
            }
            else
            {
                dp[i][sum] = dp[i+1][sum];
            }
        }
    }
    return dp[0][0];
}
