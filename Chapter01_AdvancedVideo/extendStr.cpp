#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Solution{
public:
    //在原始串上添加字符，使大串包含两个原始串并且最短
    //输入:原始字符串，输出：大串
    string extendStr(string str)
    {
        if(str.empty()) return "";//若是原始串是空的，那么返回一个空串即可
        string res = str;//初始时为原始串
        vector<int> next = getNext(str);//生成原始串的next数组
        int n = str.size(); 
        //取出str的从next[n]到最后的子串添加到res后面
        res += str.substr(next[n]);
        return res;
    }

    //获得next数组
    vector<int> getNext(string str)
    {
        //获得str的Next数组，next[i]表示str[i]之前的子数组的最长前缀和最长后缀的匹配长度
        int n = str.size();
        vector<int> next(n+1);
        //若str不是空的，那么n至少是1
        next[0] = -1;
        next[1] = 0;
        int cn = 0;//表示跳到什么位置
        int i = 2;
        while(i<=n)
        {
            if(str[i-1]==str[cn])
            {
                next[i++] = ++cn;
                //cn更新为i位置的最长前缀和最长后缀的匹配长度，为i+1位置做准备
            }
            else if(cn>0)
            {
                cn = next[cn];
            }
            else
            {
                next[i++]=0;
            }
        }
        return next;
    }
};

int main()
{
    string str;
    cin >> str;
    Solution s;
    string res = s.extendStr(str);
    cout << res << endl;
    return 0;
}
