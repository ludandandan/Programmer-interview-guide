## 拼接所有字符串产生字典序最小的字符串
[完整代码]((https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/LowestLexicography.cpp)

**题目：**
> 给定一个字符串类型的数组strs，请找到一种拼接顺序，使得将所有的字符串拼接起来组成的字符串时所有可能性中字典顺序最小的，并返回这个字符串。
> 例如strs=["abc","de"]可以拼接为"abcde"，也可以是"deabc"，但前者的字符串更小。strs=[""ba,"b"]可以拼接为"bab"或"bba"，但前者更小。

> 这个题目用到了贪心算法。定义一个比较器，若str1+str2的字典序小于str2+str1的字典序，那么就定义str1\<str2，在排序时将str1放在str2的后面。这样将整个数组中字符串按照这个规则排序后在从前到后拼接起来得到的字符串就是最小字典序字符串。可是这个并没有证明，用对数器验证是否正确即可。

```c++
bool LexicographyAscending(string str1, string str2)
{
    string str12 = str1+str2;
    string str21 = str2+str1;
    return str12 < str21;
}

string LowestLexicography(vector<string> strs)
{
    if(strs.empty()) return NULL;
    sort(strs.begin(), strs.end(), LexicographyAscending);
    string res;
    for(string s:strs)
    {
        res += s;
    }
    return res;

}

```