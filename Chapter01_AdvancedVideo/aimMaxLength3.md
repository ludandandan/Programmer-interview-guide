# 未排序数组中累加和小于等于给定值的最小子数组长度

[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/aimMaxLength3.cpp)

**题目：**

给定一个无序数组arr， 其中元素可正，可负，可0。给定一个整数k，求arr所有子数组中累加和小于或等于k的最长子数组的长度。

**举例：**

例如： arr=[3,-2,-4, 0, 6]， k=-2，相加和小于等于-2的最长子数组为{3, -2, -4, 0}， 所有结果返回4.


**要求：**

实现出时间复杂度为O(N)的方法。

**解析：**

求以每个位置开头的，累加和小于或等于k的最长子数组长度，其中最长的那个就是需要的结果。

需要计算两个额外的辅助数组。一个是min_sum（以每个位置开头的最小累加和），一个是min_sum_index（以每个位置开头的最小累加和的右边界）。

这两个数组的计算方法：

从后往前计算，假设数组arr的长度为N，那么最后一个位置arr[N-1]对应的min_sum[N-1]=arr[N-1]，min_sum_index[N-1]=N-1；再往前，若是求i位置的，那么看min_sum[i+1]是正还是负，
1. 若是正的，那么min_sum[i]=arr[i]， min_sum_index[i] = i
2. 若是负的或者是0，那么min_sum[i] = arr[i]+min_sum[i+1]，min_sum_index = min_sum_index[i+1]
   
然后从前往后看，计算以每个位置开头的，累加和小于或等于k的最长子数组长度。用一个全局变量res接住最长的长度。定义一个整型变量sum=0记录当前的累加和。定义end=0记录当前子数组窗口的最右边位置的下一个位置。

使用一个for循环变量以每个位置i开头的子数组
用i表示当前窗口的最左边，end为窗口最右边的后一个位置，即当前窗口为[i, end-1]

若是以i开头的子数组当前的sum再加上后面的一块min_sum[end]还是小于等于aim的，那么可以以i开头的子数组还可以往右扩，扩到不能再扩为止（不能再扩就是end到头了或者sum大于aim了）。当不能再扩了，现在就是以i开头的累加和小于等于aim的最长子数组，计算现在子数组的长度end-i，并用于更新res。若是一开始就扩不动，那么end=i，这样更不更新res都无所谓。计算完以i开头的了以后要计算以i+1开头的，可是这时只要把i位置从窗口中减出来，sum-=arr[i]，（注意需要检查能否减，因为当窗口中没有数（end<=i）时，就是没办法减；若是不能减，也就是窗口里没有数了，那么就让end=i+1，因为不能让end比i小啊），看以i+1开头能否让end那一块min[end]加进sum里，若是不能，那个以i+1开头的肯定不如以i开头的长，更不更新res都无所谓。

```c++
class Solution{
public:
    //累加和小于等于给定值的最长子数组
    int aimMaxLength(vector<int> arr, int  aim)
    {
        if(arr.empty() || arr.size()==0) return 0;
        //先计算两个辅助数组
        int n = arr.size();
        vector<int> min_sum(n);
        vector<int> min_sum_index(n);

        //从后往前
        min_sum[n-1] = arr[n-1];
        min_sum_index[n-1] = n-1;

        for(int i=n-2; i>=0; i--)
        {
            min_sum[i] = min_sum[i+1]<=0?arr[i]+min_sum[i+1]:arr[i];
            min_sum_index[i] = min_sum[i+1]<=0?min_sum_index[i+1]:i;
        }

        //定义一个res接住当前最长的数组长度
        //定义一个sum记录当前的累加和
        int sum = 0;
        int res = 0;
        int end = 0; 
        // i是窗口的最左位置，end是窗口最右位置的下一个位置
        for(int i=0; i<n; i++)
        {
            //while循环之后
            //若是以i开头的情况下，累加和小于或等于aim的最长子数组是arr[i,..., end]
            //看看这个子数组的长度能不能更新res
            //若是以i开头的情况下，累加和小于或等于aim的最长子数组比arr[i, ..., end]短，那么更不更新都无所谓
            while(end<n && sum+min_sum[end]<=aim)
            {
                sum += min_sum[end];
                end = min_sum_index[end]+1;
            }
            res = max(res, end-i);
            //若是窗口[i, end-1]还有数，那么把最左边的数放出来
            if(end>i) sum -= arr[i];
            else
            {
                //若是里面没有数了，说明以i开头的子数组没有满足条件的
                end = i+1;//因为开头要+1了，结尾不能比开头还小
            }
        }
        return res;
    }
};
```