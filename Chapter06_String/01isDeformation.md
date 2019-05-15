# 判断两个字符串是否为变形词
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter06_String/isDeformation.cpp)

**题目：**

给定两个字符串str1和str2，若str1和str2中出现的字符种类一样且每种字符出现的次数也一样，那么str1和str2互为变形词。请实现函数判断两个字符串是否互为变形词。

**举例：**

str1="123", str2="231"，返回true；

str1="123", str2="2331"， 返回false；

**解析：**
> 首先，若str1与str2中有一个为空或者这两个字符串长度不一致肯定不是变形词，则返回false。
> 
> 然后需要一个哈希表建立str1的词频表map，map[a]=b表示a字符在str1中出现了b次。遍历整个str1建立这个词频表。然后遍历str2，若str2中出现了map中没有的字符那么就直接返回false，若出现了map中有的字符，把map中这个字符的value即词频--，若词频小于0了，那么就返回false。若是把str2遍历完一遍了还没有返回false那么就返回true。

```c++
class Solution{
public:
    bool isDeformation(string str1, string str2)
    {
        if(str1.empty() || str2.empty() || str1.size()!=str2.size()) return false;
        unordered_map<char, int> m;
        for(char c: str1)
        {
            if(m.count(c)==0) m[c]=1;
            else m[c]++;
        }
        for(char c: str2)
        {
            if(m.count(c)==0) return false;
            else
            {
                m[c]--;
                if(m[c]<0) return false;
            }
        }
        return true;
        
    }
};
```