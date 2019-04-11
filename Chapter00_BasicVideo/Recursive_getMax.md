## 递归求数组的最大值
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/Recursive_getMax.cpp)

**题目：**
>使用递归的方法求数组的最大值，并分析此递归函数的时间复杂度

>可先将数组（范围为L\~R）二分，先求数组左边一半元素（范围为L\~mid）的最大值，再求右边一半元素（范围为mid+1\~R）的最大值，最后再比较这两个的大小返回较大的那个就是全局的最大值。递归的终止条件是当L和R相等，即L\~R范围内只剩下一个元素时，无需比较大小了，直接返回这个数。

>对于子过程划分规模一样的递归过程，可用master公式来分析其复杂度。
>
>master公式:  T(N) = aT(N/b) + o(N^{d}) 其中N为总的样本量，N/b为子问题的样本量，a为子问题的个数（这个个数只需要在代码中看到表面上进行了几次，无需进入递归过程内部），o(N^{d})为解决总问题时除了递归之外的其他过程所需要的时间。
> 
> 1.当$log_{b}a$(以b为底a的对数)>d时，时间复杂度为$O(N^{log_{b}a})$
> 
> 2.当$log_{b}a$(以b为底a的对数)=d时，时间复杂度为$O(N^{d}*log(N))$
> 
> 3.当$log_{b}a$(以b为底a的对数)<d时，时间复杂度为$O(N^{d})$

>这个问题中，b=2,a=2,d=0,故$log_{b}a=1$ < d，所以，时间复杂度为$O(N^{log_{b}a}) = O(N)$

```c++
int getMax(vector<int> &arr, int L, int R)
{
    if(L==R) return arr[L];
    int mid = L + (R-L)/2;
    int maxL = getMax(arr, L, mid);
    int maxR = getMax(arr, mid+1, R);
    return max(maxL, maxR);
}
```