## 数组排序之后相邻两数的最大差值
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/maxGap.cpp)

**题目：**
> 给定一个整型数组arr，返回排序后的相邻两数的最大差值。例如arr=[9,3,1,10]，如果排序，结果为[1,3,9,10]，9和3的差为最大差值，故返回6。若arr=[5,5,5,5]，则返回0。要求如果arr的长度为N，时间复杂度要做到O(N)。

> 若是使用排序法实现，时间复杂度O(N*logN)，若是利用桶排序的思想，可以做到时间复杂度O(N)，空间复杂度O(N)。

> 桶排序的思想。若已知一个数组里的数是[0, 60]范围内的数，那么准备0\~60这样61个桶，表示一个词频表，初始值都是0。依次遍历数组中的数，若数字为i，那么就让i桶的数++，遍历完之后再根据词频表重建出原来数组的排序之后的数组。这种排序不是基于比较的排序，但这种排序可以做到稳定性。

> 使用桶排序的思想解这道题目。
> 1. 首先遍历一遍数组arr，找到数组中的最大值和最小值记作max_num和min_num，若max_num与min_num相等，直接返回0。否则进行下面的步骤
> 2. 若数组arr共有N个数，那么我们就准备N+1个桶，把min_num放在1号桶，把max_num放在N+1号桶。堆1\~N号桶来说，他们负责的区间大小为(max_num-min_num)/N，一个数若为num，那么它将会被分配在(num-min_num)*N/(max_num-min_num)。只有N个数，却有N+1个桶，则至少有一个桶是空的，因为空桶的存在，我们敢说要求的最大差值一定不来自同一个桶的相邻数。也就是说要求的最大值一定来自桶间的相邻值（即一个桶的最小值与它前面紧邻的非空桶的最大值之间的差值）。
> 
>       第二遍遍历数组arr，将arr中的数分配到桶，对于每一个桶记录三个值，一个是桶中是否进来了数，二是当前桶中数的最小值，三是当前桶中数的最大值。
> 3. 第三遍遍历arr， 计算当前桶的最小值与其前面紧邻的那个非空桶的最大值的差值，求得全局最大差值。

```c++
int maxGap(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return 0;
    int len = arr.size();
    vector<bool> hasNumber(len+1, false);
    vector<int> maxNumber(len+1, 0);
    vector<int> minNumber(len+1, 0);
    int max_num = INT_MIN;
    int min_num = INT_MAX;

    for(int i=0; i<len; i++)
    {
        max_num = max(max_num, arr[i]);
        min_num = min(min_num, arr[i]);
    }
    if(max_num==min_num) return 0;
    for(int i=0; i<len; i++)
    {
        int bid = bucket(len, max_num, min_num, arr[i]);
        maxNumber[bid] = hasNumber[bid]?max(maxNumber[bid], arr[i]):arr[i];
        minNumber[bid] = hasNumber[bid]?min(minNumber[bid], arr[i]):arr[i];
        hasNumber[bid] = true;//这个一定要放在max或min有数了之后再变为true，而不能在循环一开始就变为true
    }

    int res = INT_MIN;
    int lastMax = maxNumber[0]; //第一个桶里肯定有数
    for(int i=1; i<=len; i++)
    {
        if(hasNumber[i])
        {
            res = max(res, minNumber[i]-lastMax);
            lastMax = maxNumber[i];
        }
    }
    return res;

}

int bucket(int len, int max, int min, int num)
{
    return (num-min)*len/(max-min);
}

```