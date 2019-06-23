# 扩展字符串使包含两个原始串
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/extendStr.cpp)

**题目：**

给定一个字符串str，请在str后面添加字符使生成一个大字符串，要求这个大字符串包含两个原始串，并且开始的位置不同。添加字符使大字符串在满足条件的情况下最短，返回生成的大字符串。

**举例：**

str="aaaaa", 生成大字符串Str="aaaaaa";

str="abcabc", 生成大字符串Str="abcabcabc";

**解析：**

找到str的最长前缀和最长后缀。然后把前缀后面的部分添加到原始串后面就可以了。例如"aaaaa"的最长前缀和最长后缀为"aaaa"，然后把前缀后面的那个a添加在原始串后面即可。在KMP算法中有生成next数组。next数组中next[i]代表的是字符串中str[i]前的字符串的最长前缀和最长后缀，现在需要整个字符串str的最长前缀和最长后缀，此时需要将Next数组再向后增加一个长度，若str长度为N，那么需要next的长度为N+1，则next[N]就是整个字符串的最长前缀和最长后缀。同样，若N>=2，那么人为规定next[0]=-1, next[1]=0，后面再依次求。求出整个next数组之后，只需要在原始串str后面补上str[next[N]...end]即可。

那么如何求next数组呢？

假设现在直到next[i-1]，要求next[i]

1. 先定义一个整型变量cn, 一开始cn=next[i-1]；
2. 然后检查str[cn]是否等于str[i-1]
   1. 若是相等，next[i]=(++cn); 同时i++；
   2. 若是不相等
      1. 若是cn>0，那么让cn=next[cn]，然后在检查str[cn]是否等于str[i-1]
      2. 若是cn=0了，那么就无法往前跳了，那么只能让next[i]=0; 同时i++计算下一个位置
   

注意使用字符串的substr方法：从字符串中取出一个子串
```c++
string substr (size_t pos = 0, size_t len = npos) const;
```
第一个参数为位置pos，那个参数为要取出的长度len。即从pos位置开始（包含Pos位置）向右取出长度为Len的子串。若是只提供Pos参数，那么就会从Pos开始取到最后
例如
```C++
string s="abcdefg"
string sub = s.substr(1,2);//sub为"bc"
string sub2 = s.substr(1);//sub2为"bcdefg"
```


```c++
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

```

