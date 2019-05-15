#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#define INT_MAX 65535
using namespace std;

class Solution{
public:
    int minCut(string s)
    {
        if(s.empty() || s.size()==1) return 0;
        int n = s.size();
        vector<int> dp(n+1);//dp[i]表示从s[i,..., end]最少需要切多少次才能全部切为回文子串
        vector<vector<bool>> p(n, vector<bool>(n));
        for(int i=0; i<n; i++) for(int j=0; j<n; j++) p[i][j]=false;
        dp[n] = -1;//没有字符不需要切割
        //从右到左
        for(int i=n-1; i>=0; i--)
        {
            dp[i] = INT_MAX;
            //j从i到end
            for(int j=i; j<n; j++)
            {
                if(s[i]==s[j] && ((j-i)<2 || p[i+1][j-1]))
                {
                    dp[i] = min(dp[i], dp[j+1]+1);
                    p[i][j] = true;
                }
            }
        }
        return dp[0];
    }
};

class Solution1{
public:
    int minCut(string s)
    {
        if(s.empty() || s.size()==1) return 0;
        int n = s.size();
        vector<int> dp(n+1, INT_MAX);//dp[i]表示[i,..., end]最少需要切多少刀
        vector<vector<bool>> p(n,vector<bool>(n));//p[i][j]表示[i,...,j]是否是回文
        for(int i=0; i<n; i++) for(int j=0; j<n; j++) p[i][j]=false;
        dp[n] = -1;
        for(int i=n-1; i>=0; i--)
        {
            for(int j=i; j<=n-1; j++)
            {
                if(((j-i<2) || (p[i+1][j-1]))&&(s[i]==s[j]))
                {
                    p[i][j] = true;
                    dp[i] = min(dp[i], dp[j+1]+1);
                }
            }
        }
        return dp[0];
    }
};

int main()
{
    string str;
    Solution s;
    Solution1 s1;
    cin >> str;
    int res = s.minCut(str);
    int res1 = s1.minCut(str);
    cout << res << endl;
    cout << res1 << endl;
    return 0;
}


