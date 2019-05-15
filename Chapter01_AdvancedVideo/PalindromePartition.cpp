#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

class Solution{
public:
    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> res;
        vector<string> out;
        dfs(s,0,out, res);
        return res;
    }

    bool isPalindrome(string s, int start, int end)
    {
        if(s.empty() || s.size()==1 ||start==end) return true;
        int i = start;
        int j = end;
        while(i<j)
        {
            if(s[i++]!=s[j--]) return false;
        }
        return true;
    }

    void dfs(string s, int start, vector<string> &out, vector<vector<string>> &res)
    {
        if(start==s.size())
        {
            res.push_back(out);
        }
        for(int i = start; i < s.size(); i++)
        {
            if(isPalindrome(s, start, i)) 
            {
                out.push_back(s.substr(start, i-start+1));
                dfs(s, i+1, out, res);//若[start,..,i]是回文，那么就再看看后面的[i+1,...]
                out.pop_back();
            }

        }
    }
};

class Solution1{
public:
    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> res;
        vector<string> out;
        dfs(s, res, out, 0);
        return res;
    }
    bool isPalindrome(string s, int start, int end)
    {
        if(s.empty() || s.size()==1 || start==end) return true;
        int i = start;
        int j = end;
        while(i<j)
        {
            if(s[i++]!=s[j--]) return false;
        }
        return true;
    }

    void dfs(string s, vector<vector<string>> &res, vector<string> &out, int start)
    {
        if(start==s.size())
        {
            res.push_back(out);
        }

        for(int i=start; i<s.size(); i++)
        {
            if(isPalindrome(s, start, i))
            {
                out.push_back(s.substr(start, i-start+1));
                dfs(s, res, out, i+1);
                out.pop_back();
            }
        }
    }

};
int main()
{
    string str;
    Solution s;
    Solution1 s1;
    cin >> str;
    vector<vector<string>> res = s.partition(str);
    vector<vector<string>> res1 = s1.partition(str);
    for(auto w: res)
    {
        for(auto m:w)
        {
            cout << m << ",";
        }
        cout << endl;
    }

    for(auto w: res1)
    {
        for(auto m: w)
        {
            cout << m << ",";
        }
        cout << endl;
    }
    return 0;
}
