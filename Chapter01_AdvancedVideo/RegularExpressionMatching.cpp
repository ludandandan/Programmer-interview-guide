#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

class solution{
public:
    bool isValid(string str, string exp)
    {
        for(int i=0; i<str.size(); i++)
        {
            if(str[i]=='.' || str[i]=='*') return false;
        }
        for(int i=0; i<exp.size(); i++)
        {
            if(exp[i]=='*' && (i==0 ||exp[i-1]=='*')) return false;
        }
        return true;
    }
    bool isMatch(string s, string p)
    {
        if(isValid(s,p))
        {
            return f(s, p, 0, 0);
        }
        else return false;
    }

    bool f(string str, string exp, int si, int ei)
    {
        if(ei==exp.size()) return si==str.size();
        else if(ei==exp.size()-1)
        {
            if((si==str.size()-1) && (exp[ei]==str[si] || exp[ei]=='.')) return true;
            return false;
        }
        else
        {
            if(exp[ei+1]!='*')
            {
                return (si!=str.size() && (exp[ei]==str[si] || exp[ei]=='.') && f(str, exp, si+1, ei+1));
            }
            else//若下一个字符是星
            {
                //若下一个字符是星，当前字符匹配
                while(si!=str.size() && (exp[ei]==str[si] || exp[ei]=='.'))
                {
                    if(f(str, exp, si, ei+2)) return true;
                    si++;
                }
                //下一个字符是星，当前不匹配
                return f(str, exp, si, ei+2);
            }
        }
    }
    bool isMatchDp0(string s, string p)
    {
        if(s.empty() && p.empty()) return true;
        //else if(s.empty() || p.empty()) return false;
        if(!isValid(s,p)) return false;
        int N = s.size();
        int M = p.size();
        vector<vector<bool>> dp(N+1, vector<bool>(M+1));
        for(int i=0; i<=N; i++) for(int j=0; j<=M; j++) dp[i][j]=false;

        dp[N][M] = true;
        // for the last col表示p已经没了，但s还剩一些字符，这时都是false;
        //对应倒数第二列，表示p还有一个字符，但s还剩一些字符
        //若s还剩一个字符且p的最后一个字符与s相同或p最后为.那么dp[N-1][M-1]是ture否则就false，其他位置都是false
        if(N>0 && M>0)  dp[N-1][M-1] = (s[N-1]==p[M-1] || p[M-1]=='.');//注意约束条件，"",".*"

        //对最后一行，表示s已经没了，但p还剩一些字符，此时只有p为X*模样，p[i]=X，p[i+1]=*，这样dp[N][i]=true,dp[N][i+1]=false
        for(int i=M-2; i>=0; i=i-2)
        {
            if(p[i+1]=='*' && p[i]!='*') dp[N][i]=true;
            else break;
        }

        //对其他普遍位置
        for(int i=N-1; i>=0; i--)
        {
            for(int j=M-2; j>=0; j--)
            {
                if(p[j+1]!='*')
                {
                    dp[i][j] = ((s[i]==p[j]||p[j]=='.') && dp[i+1][j+1]);
                }
                else
                {// j+1位置为*，若i与j匹配
                    int si = i;
                    while(si!=s.size() && (s[si]==p[j] || p[j]=='.'))
                    {
                        if(dp[si][j+2]==true) 
                        {
                            dp[i][j]=true;
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

    bool isMatchDp(string s, string p)
    {
        if(s.empty() && p.empty()) return true;
        if(!isValid(s,p)) return false;
        int N = s.size();
        int M = p.size();
        vector<vector<bool>> dp(N+1, vector<bool>(M+1));
        initDpMap(s, p, dp);

        //对其他普遍位置
        for(int i=N-1; i>=0; i--)
        {
            for(int j=M-2; j>=0; j--)
            {
                //若j+1不是*
                if(p[j+1]!='*')
                    dp[i][j] = ((s[i]==p[j] || p[j]=='.') && dp[i+1][j+1]);
                else //若j+1是*
                {
                    //若i，j匹配
                    int si = i;
                    while(si<s.size() && (s[si]==p[j] || p[j]=='.'))
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

    void initDpMap(string s, string p, vector<vector<bool>> &dp)
    {
        int N = s.size();
        int M = p.size();
        //vector<vector<bool>> dp(N+1, vector<bool>(M+1));
        for(int i=0; i<=N; i++) for(int j=0; j<=M; j++) dp[i][j] = false;
        dp[N][M] = true;
        //对最后一列，表示p没了，但是s还有一些字符，此时肯定无法匹配，都是false
        //对倒数第二列，表示p还剩一个字符，s还有0个到s.size()个字符，其中，只有s还有最后一个字符时才可匹配上
        //但是要注意不要越界
        if(N>0 && M>0)
        {
            dp[N-1][M-1] = (s[N-1]==p[M-1] || p[M-1]=='.');
        }
        //对最后一行，表示s没了，但p还有一些，此时只有p时X*模样的才可能与没了匹配上,只有两个字符一起配合才可以匹配没了
        for(int i=M-2; i>=0; i=i-2)
        {
            if(p[i]!='*' && p[i+1]=='*') dp[N][i] = true;
            else break;
        }
    }
};

class solution1{
public:
    bool isValid(string s, string p)
    {
        for(int i=0; i<s.size(); i++)
        {
            if(s[i]=='.' || s[i]=='*') return false;
        }
        for(int i=0; i<p.size(); i++)
        {
            if(p[i]=='*' && (i==0 || p[i-1]=='*')) return false;
        }
        return true;
    }

    bool isMatch(string s, string p, int si, int pi)
    {
        if(pi==p.size())//p一个字符也不剩了
        {
            if(si==s.size()) return true;
            else return false;
        }
        else if(pi==(p.size()-1))//p就剩一个字符了
        {
            if((si==(s.size()-1)) && (s[si]==p[pi] || p[pi]=='.')) return true;
            else return false;
        }
        else//p还要两个及两个以上字符
        {
            if(p[pi+1]!='*')
            {
                return (si!=s.size() && (s[si]==p[pi] || p[pi]=='.') && isMatch(s,p, si+1, pi+1));
            }
            else
            {
                //若匹配
                while(si!=s.size() && (s[si]==p[pi] || p[pi]=='.'))
                {
                    if(isMatch(s,p,si,pi+2)) return true;
                    si++;
                }
                //若不匹配
                return isMatch(s,p,si,pi+2);
            }
        }

    }
    bool isMatch(string s, string p)
    {
        if(s.empty() && p.empty()) return true;
        return isMatch(s, p, 0, 0);
    }

    bool isMatchDp(string s, string p)
    {
        if(s.empty() && p.empty()) return true;
        int m = s.size();
        int n = p.size();
        vector<vector<bool>> dp(m+1, vector<bool>(n+1));
        initDp(dp, s, p);
        
        for(int i=m-1; i>=0; i--)
        {
            for(int j=n-2; j>=0; j--)
            {
                if(p[j+1]!='*')
                {
                    dp[i][j] = ((s[i]==p[j] || p[j]=='.') && dp[i+1][j+1]);
                }
                else
                {
                    int si = i;
                    while(si!=m && (s[si]==p[j] || p[j]=='.'))
                    {
                        if(dp[si][j+2])
                        {
                            dp[i][j] = true;
                            break;
                        }
                        si++;
                    }
                    if(!dp[i][j]) dp[i][j] = dp[si][j+2];
                }
            }
        }
        return dp[0][0];
    }

    void initDp(vector<vector<bool>> &dp, string s, string p)
    {
        int m = s.size();
        int n = p.size();
        for(int i=0; i<=m; i++) for(int j=0; j<=n; j++) dp[i][j]=false;
        dp[m][n] = true;
        //最后一列，p没了，s还有一堆是不可能匹配的
        //倒数第二列，p还剩一个，s还有一堆，只有s还剩一个并且s最后一个字符与p最后一个字符匹配了，才是true
        if(m>0 && n>0 &&(s[m-1]==p[n-1]||p[n-1]=='.'))
        {
            dp[m-1][n-1] = true;
        }
        //对最后一行，s没了，但p还有一堆，只有p是X*的模样才可能匹配
        for(int i=n-2; i>=0; i=i-2)
        {
            if(p[i+1]=='*' && p[i]!='*')
            {
                dp[m][i] = true;
            }
            else break;
        }
    }
};



int main()
{
    string str = "abc";
    string exp = "ab*";
    //cin >> str;
    //cin >> exp;
    
    solution s;
    solution1 s1;
    bool res = s.isMatchDp(str, exp);
    bool res1 = s1.isMatchDp(str, exp);
    cout << res << endl;
    cout << res << endl;
    return 0;
}
