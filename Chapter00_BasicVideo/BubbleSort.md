## 冒泡排序
[完整代码]()

**题目：**
> 冒泡排序细节及复杂度分析。数组长度为N。

> 相邻的两两排序，最大的沉底，然后最大的不管了，再排0~end-1的数。第一遍遍历N个数，第二遍N-1个数，直到最后1个数，等差数列求和，不要低阶项和高阶项的次数，最后时间复杂度$O(N^{2})$。

```c++
void BubbleSort(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    for(int end=arr.size()-1; end>0; end--)
    {
        for(int i=0; i<end; i++)
        {
           if(arr[i]>arr[i+1]) swap(arr, i, i+1); 
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