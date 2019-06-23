#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Solution{
public:
    //str[i,..]能否被exp[j,..]的匹配出来
    bool f(string str, string exp, int i, int j)
    {
        //若j已经没有字符了，那么str也必须没有字符
        if(j==exp.size()) return i==str.size();

        //j后面没有字符了，或者j后面的字符不是*,
        //那么str[i]必须与str[j]匹配上，否则直接返回false
        //若前面匹配上了，后面还有看f(i+1,j+1)
        if((j+1)==exp.size() || exp[j+1]!='*')
        {
            return ((i!=str.size()) && (str[i]==exp[j]||exp[j]=='.') && f(str, exp, i+1, j+1));
        }
        //若是j+1有字符并且是*,
        //若是str[i]与exp[j]能配上
        while(i!=str.size() && (str[i]==exp[j]||exp[j]=='.'))
        {
            if(f(str, exp, i, j+2)) return true;
            i++;
        }
        //若是j+1有字符且是*，但是str[i]与exp[j]不匹配
        return f(str, exp, i, j+2);
    }

    bool isMatch(string str, string exp)
    {
        if(str.empty() && exp.empty()) return true;
        //if(str.empty() || exp.empty()) return false;
        return f(str, exp, 0, 0);
    }

    bool isMatch2(string str, string exp)
    {
        if(str.empty() && exp.empty()) return true;

        int n = str.size();
        int m = exp.size();
        vector<vector<bool>> dp(n+1, vector<bool>(m+1));
        //初始化为flase;
        for(int i=0; i<=n; i++) for(int j=0; j<=m; j++) dp[i][j] = false;

        //填最后一列, exp没有字符了，只有str也没有字符才是true，其他false
        dp[n][m] = true;
        //填最后第二列，exp还有一个字符（exp必须不是空的才可以），
        //那么只有str还有一个字符并且和exp匹配上才可以（str也必须不是空）
        if(n>0 && m>0) 
        {
            if(str[n-1]==exp[m-1] ||exp[m-1]=='.')
            dp[n-1][m-1] = true;
        }
        //填最后一行，str没有字符了，exp还有一些，只有exp没了，
        //或者至少两个并且是X*模式的才可以是ture
        for(int j=m-2; j>=0; j=j-2)
        {
            //两个两个的
            if(exp[j]!='*' && exp[j+1]=='*') dp[n][j] = true;
            else break;
        }
        //目标是dp[0][0]
        for(int i=n-1; i>=0; i--)
        {
            for(int j=m-2; j>=0; j--)
            {
                //若是j+1不是*
                if(exp[j+1]!='*')
                {
                    dp[i][j] = ((str[i]==exp[j]||exp[j]=='.') && dp[i+1][j+1]);
                }
                //若j+1是*
                else
                {
                    int si = i;
                    while(si!=n && (str[si]==exp[j] || exp[j]=='.'))
                    {
                        if(dp[si][j+2]) 
                        {
                            dp[i][j]=true;
                            break;
                        }
                        si++;       
                    }
                    if(dp[i][j]!=true) dp[i][j]=dp[si][j+2];
                }
            }
        }
        return dp[0][0];
        
    }
};

int main()
{
    string str="";
    string exp=".*";
    Solution s;
    bool res = s.isMatch(str, exp);
    cout << res << endl;
    bool res2 = s.isMatch2(str, exp);
    cout << res2 << endl;
    return 0;
}
