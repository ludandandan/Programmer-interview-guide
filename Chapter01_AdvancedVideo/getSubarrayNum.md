# 最大值减去最小值小于或等于num的子数组数量
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/getSubarrayNum.cpp)

**题目：**

给定数组arr和整数num，共返回有多少个子数组满足如下情况：

max(arr[i,...,j]) - min(arr[i,...,j]) <=num

max(arr[i,...,j])表示子数组arr[i,...,j]中的最大值， min(arr[i,...,j])表示子数组arr[i,...,j]中的最小值。

**要求：**

如果数组长度为N，请实现时间复杂度O(N)的解法。


**解析：**

一种暴力解法：穷举所有的子数组（子数组必须是连在一起的），然后检查每一个子数组是否满足max(arr[i,...,j]) - min(arr[i,...,j]) <=num的条件。对于一个长度为N的子数组，子数组的数量为O(N^2)个（以0开头的子数组有N个，以1开头的有N-1个。。。等差数列求和）。以两个整型变量start和end表示子数组的范围[start, end]（其中start从0到n-1, end从start到n-1），然后遍历子数组arr[start,...,end]得到其最大值和最小值，相减判断是否满足条件。这样暴力方法总体的时间复杂度是O(N^3).

一个基本规律：
1. 若一个子数组满足条件，那么这个子数组内部的所有子数组也肯定满足条件。
2. 若一个子数组不满足条件，那么这个包含这个子数组的所有子数组也肯定不满足条件
   
根据上面的基本规律，我们可以一次求出以i开头的所有子数组的数量，在res中不是加一个数而是加上一堆数。以i开头的子数组有(i~i, i~i+1, i~i+2, ..., i~n-1)，求每个子数组的最大值和最小值可以用窗口内最大值和最小值的更新结构很快求出来。根据最大值和最小值判断当前以i开头的这个子数组是否满足条件，若满足，那么右边界还可以向右扩，若不满足，那么右边界就没有必要向右扩检查了，因为基本规律2告诉我们后面不可能有满足条件的了。假设右边界r扩到x就不能向右扩了（x刚好不行），那么以i开头的满足条件的子数组就有x-i个，直接在res里加上x-i。然后换新的开头位置，先检查若是换开头位置的话当前队列的头会不会过期，若是会，那么就先把它弹出来，然后开头位置（即窗口左边界l）++。

虽然使用了两个while循环，外循环控制开头位置即窗口左边界l，内循环控制窗口右边界r，但是对于数组里的数，都是进窗口一次，出窗口一次，所有时间复杂度为O(N)。


```c++
class getSubarrayNum{
public:
    //暴力方法：穷举所有的子数组，然后检查是否满足条件O(N^3)
    int getNum1(vector<int> arr, int num)
    {
        //子数组的范围[start, end]
        int start = 0;
        int end = 0;
        int res = 0;
        for(; start<arr.size(); start++)
        {
            for(end=start; end<arr.size(); end++)
            {
                if(isValid(arr, start, end, num)) res++;
            }
        }
        return res;
    }

    bool isValid(vector<int> &arr, int start, int end, int num)
    {
        int max_val = INT_MIN;
        int min_val = INT_MAX;
        for(int i=start; i<=end; i++)
        {
            max_val = max(max_val, arr[i]);
            min_val = min(min_val, arr[i]);
        }
        return (max_val-min_val)<=num;
    }
    //使用窗口来实现

    int getNum2(vector<int> arr, int num)
    {
        //若一个子数组满足条件，那么这个子数组内部的所有子数组肯定都满足条件
        //若一个子数组不满足条件，那么包含这个子数组的所有子数组肯定都不满足条件
        deque<int> min_deq;//窗口内最小值的更新结构
        deque<int> max_deq;//窗口内最大值的更新结构
        int l = 0; //窗口的左边界
        int r = 0; //窗口的右边界
        int res = 0;
        //每次计算必须以l开头的子数组中满足条件的个数
        while(l<arr.size())
        {
            while(r<arr.size())
            {
                //r一直向右，并更新min_deq和max_deq，
                //直到r到某个位置不满足max-min<=num的条件了就停，跳出内循环
                while(!min_deq.empty() && arr[min_deq.back()]>=arr[r])
                {
                    min_deq.pop_back();
                }
                min_deq.push_back(r);

                while(!max_deq.empty() && arr[max_deq.back()]<=arr[r])
                {
                    max_deq.pop_back();
                }
                max_deq.push_back(r);
                
                if(arr[max_deq.front()]-arr[min_deq.front()] >num) break;
                r++;
            }

            res += r-l;
            //接下来要换新的开始位置l了
            //首先检查现在的队列的头是否即将过期，若是就弹出来
            if(max_deq.front()==l) max_deq.pop_front();
            if(min_deq.front()==l) min_deq.pop_front();
            l++;
        }
        return res;
    }
};
```