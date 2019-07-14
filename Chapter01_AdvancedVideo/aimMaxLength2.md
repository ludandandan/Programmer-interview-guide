# 未排序正数组累加和等于给定值的子数组
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/aimMaxLength2.cpp)

**题目：**

给定一个数组arr，都是正数，一个整数aim，求累加和等于aim的最长子数组。

**要求：**

额外空间复杂度O(1)，时间复杂度O(N)

**解析：**

可以使用双指针的方法。一个L指针一个R指针。一开始都指在0位置，然后用一个全局变量sum记录当前窗口里的数的和，一个全局变量maxLen记录当前找到的最长子数组长度。

当R指针不越界时，比较sum与aim的大小：
    
    1. 若是sum<aim，那么就把R指针向右移动，更新sum
    2. 若是sum>aim，那么就把L指针向右移动，更新sum
    3. 若是sum==aim，那么就把这个(R-L+1)与当前的maxLen比较并更新，然后R向右移动，更新sum


```c++
class Solution{
public:
    int aimMaxLength(vector<int> arr, int aim)
    {
        if(arr.empty() || arr.size()==0) return 0;
        int L = 0;
        int R = 0;
        int maxLen = INT_MIN;
        int sum = arr[0];
        while(R!=arr.size())
        {
            if(sum==aim)
            {
                maxLen = max(maxLen, R-L+1);
                sum += arr[++R];
            }
            else if(sum<aim)
            {
                sum += arr[++R];
            }
            else
            {
                sum -= arr[L++];
            }
        }
        return maxLen;
    }
};
```
   
