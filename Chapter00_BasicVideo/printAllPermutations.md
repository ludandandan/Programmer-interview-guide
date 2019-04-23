## 打印一个字符串的全排列
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/printAllPermutations.md)

**题目：**
> 打印一个字符串的全排列。例如打印字符串"abc"的全排列："abc", "acb", "bac", "bca", "cab", "cba"。

> 对于每个位置0\~n-1(长度为n的字符串)，都有与后面位置的字母交换和不交换两种选择。对于不交换可以想象成与自己交换。所以对于每个位置，与自己及以后位置的字母进行交换。定义一个变量k，表示进行k位置的字母了，那么需要k位置的字母与[k,n-1]位置上的元素逐个交换。交换之后将k+1继续进行递归。base case是当k==str.size()时，就是处理完所有元素了，就打印当前的str，然后返回。注意swap时是直接在原str上进行操作的。

```c++
void printAllPermutations(string str)
{
    process(str, 0);
}

void process(string str, int k)
{
    if(k==str.size())
    {
        cout << str << endl;
        return;
    }
    for(int i=k; i<str.size(); i++)
    {
        swap(str, i, k);
        process(str, k+1);
    }
}


void swap(string &str, int i, int j)
{
    char ch = str[i];
    str[i] = str[j];
    str[j] = ch;
}
```