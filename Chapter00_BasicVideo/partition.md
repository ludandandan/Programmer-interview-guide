## Partition问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/partition.cpp)

**题目：**

> 给定一个数组arr和一个数Num，请把小于等于num的数放在数组的左边，大于num的数放在数组的右边。要求额外空间复杂度O(1)，时间复杂度O(N)。

> 定义一个指针less指向数组的首元素之前，表示less及less的左边都是小于等于num的，遍历整个数组，假设当前处理的元素为cur=arr[i]，若cur<=num，那么将cur与less的下一个元素arr[less+1]交换同时less往下移动一个，表示小于等于区域往右边扩了一个数。若cur>num，那么什么都不做，继续处理下一个数。当遍历完整个数组时，less及less右边为小于等于区域，左边为大于区域。partition操作不具有稳定性。

```c++
void partition(vector<int> &arr, int num)
{
    if(arr.empty() || arr.size()<2) return;
    int less = -1;
    for(int i=0; i<arr.size(); i++)
    {
        if(arr[i]<=num)
        {
            swap(arr, i, ++less);
        }
    }
}

void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
```