#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define INT_MAX 65535
using namespace std;


void dfs(string s, int start, vector<vector<string>> &res, vector<string> &out);
//判断当前字符串是否是回文
bool isValid(string s, int i, int j);
//返回所有的回文切割方式
vector<vector<string>> partition(string s);


class minCut{
public:
    int minCutDp(string s)
    {
        if(s.empty() || s.size()==1) return 0;
        int n = s.size();
        vector<int> dp(n+1, 0);
        dp[n] = -1;
        dp[n-1] = 0;
        //用一个vector记录[i,...,j]是否是回文
        vector<vector<bool>> p(n, vector<bool>(n));
        //初始化为flase
        for(int i=0; i<n; i++) for(int j=0; j<n; j++) p[i][j] = false;
        //依次计算以i开始到结尾的子串的回文最小切割数，放到dp[i]里
        for(int i=n-1; i>=0; i--)
        {
            dp[i] = INT_MAX;
            for(int j=i; j<n; j++)
            {
                if(s[i]==s[j] && (j-i<2 || p[i+1][j-1]))
                {
                    dp[i] = min(dp[i], dp[j+1]+1);
                    p[i][j] = true;
                }
            }
        }
        return dp[0];
    }
};


//返回所有的回文切割方式
vector<vector<string>> partition(string s)
{
    vector<vector<string>> res;
    if(s.empty()) return res;
    vector<string> out;
    int start = 0;
    dfs(s, 0, res, out);
    return res;
}

//判断当前字符串是否是回文
bool isValid(string s, int i, int j)
{
    if(i==j) return true;
    while(i<j)
    {
        if(s[i++]!=s[j--]) return false;
    }
    return true;
}

void dfs(string s, int start, vector<vector<string>> &res, vector<string> &out)
{
    if(start==s.size()) res.push_back(out);
    for(int i=start; i<s.size(); i++)
    {
        if(isValid(s, start, i)) 
        {
            out.push_back(s.substr(start, i-start+1));
            dfs(s, i+1, res, out);
            out.pop_back();
        }
    }
}
int main()
{
    string s;
    cin >> s;
    minCut m;
    int res = m.minCutDp(s);
    cout << res << endl;
    vector<vector<string>> res2 = partition(s);
    for(auto m: res2)
    {
        for(auto r: m)
        {
            cout << r << ",";
        }
        cout << endl;
    }
    return 0;
}
