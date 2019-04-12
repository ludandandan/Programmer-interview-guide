## 求数组中的逆序对
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/print_ReverseOrderPair.cpp)

**题目：**
> 在一个数组中，左边的数比右边大，则这两个数构成一个逆序对，打印所有逆序对。例如数组 [1,3,4,5,2] 的逆序对为 (3,2), (4,2), (5,2)。

> 类似求小和问题是求一个数的左边有哪些数比他小，可以使用归并排序求出一个数cur的右边有哪些数比他大，大的个数为m则这一批小和为m*cur。逆序对问题是求一个数的左边有哪些数比他大，可以转换为求右边有哪些数比他小。

> 1. 假设左组为l[]，右组为r[]，此时两组组内已经有序，要采用外排的方式使两组合并为一个有序的大组。假设当前外排的是l[i]与r[j]。

> 2. 若r[j]<l[i]，则产生逆序对(l[i], r[j])。由于左边组已经排好序了，r[j]<l[i]，则r[j]也肯定小于l组中从i开始到l组结束的所有数，且这些数都在r[j]的左边，故r[j]与这些数都产生逆序对。由r[j]所产生的逆序对的个数为mid-j+1个。

> 3. 若r[j]>l[i]，则不产生逆序对。

> 4. 整个归并排序过程不发生改变，只是在组间合并时产生逆序对。时间复杂度与归并排序相同O(Nlog(N))。T(N) = 2T(N/2)+O(N)。空间复杂度O(N)。我老是忘记把merge时产生的help数组拷贝回原来的数组，一定不能再忘了！

```c++
void printReverseOrderPair(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    mergeSort(arr, 0, arr.size()-1);
}

void mergeSort(vector<int> &arr, int L, int R)
{
    if(L==R) return;
    int mid = L + ((R-L)>>1);
    mergeSort(arr, L, mid);
    mergeSort(arr, mid+1, R);
    merge(arr, L, mid, R);
}

void merge(vector<int> &arr, int L, int mid, int R)
{
    vector<int> help(R-L+1);
    int pl = L;
    int pr = mid+1;
    int i = 0;
    while(pl<=mid && pr<=R)
    {
        if(arr[pr]<arr[pl])
        {
            int j = pl;
            while(j<=mid)
            {
                cout << '(' << arr[j++] << ',' << arr[pr] << ')';
            }
        }
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
        arr[L+i] = help[i];
    }
}

```
