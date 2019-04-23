## 打印字符串的全部子序列
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/printAllSubsquences.cpp)

**问题：**
> 打印一个字符串的全部子序列，包括空字符串。例如打印"abc"的全部子序列："", "a", "ab", "ac", "abc", "b", "bc", "c"。不用在意顺序。

> 使用递归的方式。字符串中的每个字符都有两种选择：打印和不打印。定义一个变量i表示目前进行到哪个字符了。还需要定义一个string res表示当前拼接好的答案。base case就是当i==str.size()时就是所有字符“要和不要”都决定好了，此时就打印上一级已经决定好的res。若没到最好一个字符，那么就由现在的res开始走两条路，要str[i]和不要str[i]，然后i+1。

```c++
void printAllSubsquences(string str)
{
    if(str.empty()) return;
    string res;
    process(str, res, 0);
}

void process(string str, string res, int i)
{
    if(i==str.size()) 
    {
        cout << res << endl;
        return;
    }
    process(str, res, i+1);
    process(str, res+str[i], i+1);
}
```