#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

class match{
public:
    bool isMatch(string str, string exp)
    {
        if(str.empty() && exp.empty()) return true;
        return process(str, exp, 0, 0);
    }

    bool process(string str, string exp, int si, int ei)
    {
        //情况一：ei到最后了
        if(ei==exp.size()) return si==str.size();
        //情况二：ei还剩下一个,那么si也应该剩一个
        if(ei==exp.size()-1) return (si==str.size()-1)&&(str[si]==exp[ei]||exp[ei]=='.');
        //情况三：ei还剩下很多
        //再根据ei+1是否是*分类
        if(exp[ei+1]!='*') return (si!=str.size()) &&(str[si]==exp[ei]||exp[ei]=='.') && process(str, exp, si+1, ei+1);
        //若ei+1是*
        while(si!=str.size() && (str[si]==exp[ei] || exp[ei]=='.'))
        {
            if(process(str, exp, si, ei+2)) return true;
            si++;
        }
        return process(str, exp, si, ei+2);//表示*表示0个前面的字符（因为没有进入while）
    }
    bool isMatch2(string str, string exp)
    {
        if(str.empty() && exp.empty()) return true;
        int s = str.size();
        int e = exp.size();
        
        //建动态规划表并初始化
        vector<vector<bool>> dp(s+1, vector<bool>(e+1));
        //先全部初始化为false
        for(int i=0; i<=s; i++) for(int j=0; j<=e; j++) dp[i][j] = false;
        //最后
        dp[s][e] = true;//两个都到了最后
        //最后一列，表示exp到了最后，但是str还有，那么就是false
        //倒数第二列，首先要确定有倒数第二列，也就是exp的长度大于等于1
        //倒数第二列表示exp还有一个，那么只能str还有一个，且匹配
        if(e>=1 && s>=1 && (str[s-1]==exp[e-1] || exp[e-1]=='.')) 
        {
            dp[s-1][e-1]=true;
        }
        //最后一行，str没有了，但是exp还有,只有exp是X*形式才可以
        for(int i=e-2; i>=0; i=i-2)
        {
            if(exp[i]!='*' && exp[i+1]=='*') dp[s][i]=true;
            else break;
        }

        //对其他普遍位置
        for(int i=s-1; i>=0; i--)
        {
            for(int j=e-2; j>=0; j--)
            {
                //先一列一列的
                if(exp[j+1]!='*') dp[i][j] = ((str[i]==exp[j] || exp[j]=='.') && dp[i+1][j+1]);
                else
                {
                    int si = i;
                    while(si!=s && (str[si]==exp[j] || exp[j]=='.'))
                    {
                        if(dp[si][j+2])
                        {
                            dp[i][j] = true;
                            break;
                        }
                        si++;
                    }
                    if(dp[i][j]!=true)
                    {
                        dp[i][j] = dp[si][j+2];
                    }
                }
            }
        }
        return dp[0][0];

        
    }
};

int main()
{
    match m;
    string str = "aab";
    string exp = "c*a*b";
    bool res = m.isMatch(str, exp);
    cout << res << endl;
    bool res2 = m.isMatch2(str, exp);
    cout << res2 << endl;
    return 0;
}
