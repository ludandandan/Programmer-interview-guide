## 小和问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/smallSum.cpp)

**题目：**
> 求数组的小和。以数组 s=[1,3,5,2,4,6] 为例，在s[0]左边小于等于s[0]的数的和为0，在s[1]左边小于等于s[1]的数的和为1，在s[2]左边小于等于s[2]的数的和为1+3=4，在s[3]左边小于等于s[3]的数的和为1，在s[4]左边小于等于s[4]的数的和为1+3+2=6，在s[5]左边小于等于s[5]的数的和为1+3+5+2+4=15，整个数组的小和为0+1+4+1+6+15=27。

>可以使用遍历的方法获得小和，时间复杂度$O(N^{2})$。也可在归并排序的过程中，利用组间合并merge时产生小和，时间复杂度$O(N*log(N))$，空间复杂度O(N)。下面采用的是后者。

>1.假设左组为l[]，右组为r[]，此时左右两组已经组内有序，要利用外排的方式组成一个有序的大组。假设当前外排是l[i]与r[j]进行比较。

>2.若l[i]<=r[j]则产生小和，并且r[]组中从j开始到r组结束的这些数的小和里都包含l[i]，因为这些数都比r[j]大，也就比l[i]大，同时又在l[i]的右边。相当于找右边有哪些数比cur大，就产生多少个cur小和。假设从r[j]到r组结束共有m（m=R-j+1）个数，则产生的小和为m*l[i]。

>3.若l[i]>r[j]则不产生小和

>4.整个归并排序过程该怎么进行怎么进行，排序过程没有任何变化，只是利用组间合并的过程累加所有产生的小和，总共的累加和就是结果。归并排序无返回值，可是这里要有一个int类型的返回值用于返回累加得到的小和。总的小和来自三个方面：左边归并排序产生的小和+右边归并排序产生的小和+两边merge时产生的小和。

```c++
int smallSum(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return 0;
    return mergeSort(arr, 0, arr.size()-1);
}

int mergeSort(vector<int> &arr, int L, int R)
{
    if(L==R) return 0;
    int mid = L + ((R-L)>>1);
    return mergeSort(arr, L, mid) + mergeSort(arr, mid+1, R) +
        merge(arr, L, mid, R);
}

int merge(vector<int> &arr, int L, int mid, int R)
{
    vector<int> help(R-L+1);
    int pl = L;
    int pr = mid+1;
    int i = 0;
    int res = 0;
    while(pl<=mid && pr<=R)
    {
        res += arr[pl]<=arr[pr]? arr[pl]*(R-pr+1):0;
        help[i++] = arr[pl]<=arr[pr]? arr[pl++]:arr[pr++];
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
    return res;
}

```