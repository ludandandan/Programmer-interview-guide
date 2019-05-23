# 在有序但含有空的数组中查找字符串
[完整代码]()

**题目：**

给定一个字符串数组strs，在strs中有些位置为null，但在不为null的位置上，
其字符串是按照字典顺序由小到大依次出现的。
再给定一个字符串str，请返回str在strs中出现的最左的位置。

**举例：**

strs=[null, "a", null, "a", null, "b", null, "c"]，str="a"，返回1；
strs=[null, "a", null, "a", null, "b", null, "c"]，str=null，只要str为null就返回-1；
strs=[null, "a", null, "a", null, "b", null, "c"]，str="d"，返回-1；


**解析：**

尽可能多的应用二分法。

1. 假设在strs[l,...,r]上进行查找。需要一个整型变量res用于保存str在strs中出现的最左位置。需要整型变量mid，用于二分。初始时,l=0,r=strs.size()-1,mid=0, res=-1(res一定必须要等于-1，因为若是在后面的过程中没有找到合适的就会返回初始值-1)
2. 只要l<=r就进行如下循环
   1. 首先计算mid=l+(r-l)/2，mid必须在训练里面计算
   2. 然后检查当前strs[mid]是否与str相等，若是相等，就找到了str在strs中的一个位置，令res = mid，但要找更左的位置，所以再在左半边找，也就是令r=mid-1;若是不相等那么就进行下面的操作。
   3. 检查strs[mid]是否是null(实际是"")。
      1. 若不是空，那么就按照普通的二分法进行。即strs[mid]<str的话在右半边找，令l=mid+1， 若strs[mid]>str的话在左边找，令r=mid-1;
      2. 若是空的，那么就检查左半边[l,...,mid-1]，从右往左检查(注意不用越界)，找到第一个不是null的位置i。
         1. 若这个位置i超过l了，也就是越界了或者strs[i]比str小，那么一定不在左半边，就到右半边去找，即令l = mid+1;
         2. 若这个位置没越界，并且strs[i]与str相等，那么就是找到了一个str在strs中的位置，令res=i，但还得向左找，令r=mid-1;
         3. 若这个位置没越界，并且strs[i]>str。说明还得往左找，令r=mid-1

```c++
class Solution{
public:
    int getIndex(vector<string> &strs, string str)
    {
        if(strs.empty() || str.empty()) return -1;
        int n = strs.size();
        int l = 0;
        int r = n-1;
        int mid = 0;
        int res = -1;//一开始必须为-1，因为若是下面的while找不到就会返回初始值-1
        while(l<=r)
        {
            mid = l + (r-l)/2;
            //若中间正好是str，为了取得最左，再向左半边查找
            if(strs[mid]==str)
            {
                res = mid;
                r = mid-1;
            }
            //若mid不是空
            else if(strs[mid]!="")
            {
                //若mid比str小，那么检查右半边
                if(strs[mid]<str) l = mid+1;
                else r = mid-1;
            }
            else //若Mid是空的
            {
                //先检查左半边l,...,mid-1，从右向左，直到一个不为空的位置
                int i = mid-1;
                while(i>=l)
                {
                    if(strs[i]!="") break;
                    else i--;
                }
                if(i<l || strs[i]<str) l = mid+1;
                else if(strs[i]==str)
                {
                    res = i;
                    r = i-1;
                }
                else r = i-1;
            }
        }
        return res;
    }
};
```