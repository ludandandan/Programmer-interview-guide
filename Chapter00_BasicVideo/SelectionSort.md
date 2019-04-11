## 选择排序
[完整代码]()

**题目：**
> 选择排序细节及复杂度分析。数组长度N。

> 先在0~N-1上找到最小的放在0位置，然后在1~N-1上找到最小的放到1位置...第一个循环先确定开头的位置i(0~N-2，最后只剩一个数N-1时无需比较交换了)，里面的循环从i+1开始到N-1遍历，找到最小的数的索引index，然后将这个数与i位置的数交换。min_index最开始时可设置为i，后面遇到更小的数再更新。第一次遍历N个数，第二次N-1个数，直到最后1个数，等差数列求和，忽略低阶项和高阶项的系数，时间复杂度$O(N^{2})$。空间复杂度O(1)。

```c++
void SelectionSort(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    for(int i=0; i<arr.size()-1; i++)
    {
        int min_index = i;
        for(int j=i+1; j<arr.size(); j++)
        {
            min_index = arr[min_index]>arr[j]?j:min_index;
        }
        swap(arr, i, min_index);
    }
}

void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
```