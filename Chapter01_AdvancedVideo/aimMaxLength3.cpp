#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

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

int main()
{
    vector<int> arr{3, -2, -4, 0, 6};
    int aim = -2;
    Solution s;
    int res = s.aimMaxLength(arr, aim);
    cout << res << endl;
    return 0;
}
