## 插入排序
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/InsertSort.cpp)

**题目：**
> 插入排序细节及复杂度分析。数组长度N。

> 插入排序是依次排好0\~0范围，0\~1范围，0\~2范围...0\~N-1范围上的数。外层循环，依次处理1\~N-1的数，(0位置上的数自然认为已经排好序了)，当处理i位置上的数时，0\~i-1位置的数已经排好序了，i位置上的数依次向前比较，若前面的数比它大就交换，一直比较到前面的数不比他大了或是到0位置（再往前就越界了）停。时间复杂度与数据状况有关，最好的情况，数组原本就是从小到大排好序的了，那么就只需遍历一遍，时间复杂度O(N)；最差情况，数组原本是按照从大到小的顺序排序，此时时间复杂度$O(N^{2})$。当时间复杂度与数据状况有关时一律按照最差情况来计算时间复杂度，故插入排序的时间复杂度为$O(N^{2})$。空间复杂度O(1)。

```c++
void InsertSort(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    for(int i=1; i<arr.size(); i++)
    {
        for(int j=i-1; j>=0&&arr[j]>arr[j+1]; j--)
            swap(arr, j, j+1);
    }
}

void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

```