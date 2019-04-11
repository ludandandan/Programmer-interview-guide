## 归并排序
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/MergeSort.cpp)

**题目：**
> 归并排序细节及复杂度分析，数组长度N。

> 归并排序使用分治的思想。先二分，左侧先排好序，右侧再排好序，然后采用外排的方式将排好序的两个子数组merge起来。这样将大问题划分为两个小问题，小问题再划分，直到递归的终止条件：只剩一个数不用排序。merge的时候，创建一个help数组，小的填，依次动，将Left和Right子数组合并再help里，然后将help拷贝到原来的arr中。时间复杂度分析使用master公式，b=2, a=2, merge的时候指针需划过N个数，故d=1,所以时间复杂度O(N*log(N))。由于创建了一个help数组，故空间复杂度O(N)。

```c++
void MergeSort(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    sortProcess(arr, 0, arr.size()-1);
}

void sortProcess(vector<int> &arr, int L, int R)
{
    if(L==R) return; //只剩一个数，无需排序了。返回上一层递归进行Merge操作
    int mid = L+((R-L)>>1);
    sortProcess(arr, L, mid);
    sortProcess(arr, mid+1, R);
    merge(arr, L, mid, R);
}

void merge(vector<int> &arr, int L, int mid, int R)
{
    vector<int> help(R-L+1);
    int pl = L;//指向左边的第一个数
    int pr = mid+1;//指向右边的第一个数
    int i = 0;//指向help数组的第一个数
    while(pl<=mid && pr<=R)
    {
        help[i++] = arr[pl]<arr[pr]?arr[pl++]:arr[pr++];
    }
    while(pl<=mid)
    {
        help[i++] = arr[pl++];
    }
    while(pr<=R)
    {
        help[i++] = arr[pr++];
    }
    for(int i=0; i<help.size(); i++)
    {
        arr[i+L] = help[i];
    }
}
```