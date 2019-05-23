#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <deque>
#define INT_MIN -65535
#define INT_MAX 65534
using namespace std;

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

int main()
{
    getSubarrayNum n;
    vector<int> arr{1,23,4};
    int num = 10;
    int res = n.getNum1(arr, num);
    cout << res << endl;
    int res2 = n.getNum2(arr, num);
    cout << res2 << endl;
    return 0;
}
