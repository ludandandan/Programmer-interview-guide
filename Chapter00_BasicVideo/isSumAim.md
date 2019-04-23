## 数组中任意个数的累加能否得到aim
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isSumAim.cpp)

**题目：**
> 给你一个数组arr和一个整数aim， arr中的数字都是正数，aim也为正数。如果可以任意选择arr中的数字，能不能累加得到aim，返回true或false。

> 方法一： 暴力递归
> 
> 这个题目与求字符串的所有子序列问题差不多。对于每个位置的数字都有要和不要两种选择。定义一个函数f(aim, arr, i, sum)，aim和arr都是题目中给的，其中i表示从i位置及其后面的数字中任意选择再加上sum看能不能累加得到aim（就是i位置之前的数已经确定了加或不加导致得到了sum，然后接着确定下i位置加或不加，后面还要确定一下i位置后面的加或不加），sum表示之前形成的累加和。要求的是f(0,0)，第一个0表示从0位置及其之后的数字自由选择能不能加出aim来，第二个0表示之前（的位置确定好了加或不加导致得到）形成的和为0。base case是当i==arr.size()时，即确定好最后一个位置加或不加后，得到的sum若刚好等于aim那么就返回true，否则就返回false。f(i,sum)有两个分支，将arr[i]加到sum上和不将arr[i]加到sum上，不管走哪条路，只要确定了i位置的选择i就要+1。

```c++
bool isSumAim(vector<int> arr, int aim)
{
   return isSumAim(arr, aim, 0, 0); 
}
bool isSumAim(vector<int> arr, int aim, int i, int sum)
{
// 之前形成的和为sum，从i位置及它之后的数中任意选择能不能组成aim
//对每个位置的数都有要和不要两种选择
    if(i==arr.size())
    {
        return aim==sum;
    }
    return isSumAim(arr, aim ,i+1, sum+arr[i]) || isSumAim(arr, aim, i+1, sum);
}
```

> 由暴力递归转换到动态规划
> 1. 看看这个暴力递归是否是无后效性的，若是就可转为动态规划，否则就不行。比如有数组arr=[2,3,5]，aim=5，那么若要2要3不要5得到f(3,5)=ture，和不要2不要3要5得到的f(3,5)结果一样，不受到达状态的路径影响，该问题是无后效性问题。
> 2. 看看递归中的哪些变量可以用于代表状态。其中aim和arr都是题目给的，无论对哪个状态来说都一样，而不同的i和sum对应不同的状态，i和sum一旦确定了，那么状态也就跟着确定了。故使用参数i和sum代表状态，dp为一个二维表。接下来需要确定参数的范围以确定dp的大小。对应i，可由递归中看到它从0到arr.size()，故它的范围为[0, arr.size()]，而对于sum，最小值是0，什么数都不选，最大值就是将数组中所有数加起来（因为是正数）S，由此也确定了范围。
> 3. 看看要求的状态是哪一个，对于这个问题就是f(0,0)，即i=0, sum=0。
> 4. 回到递归的base case中找到不受其他状态影响的状态，就是最后一行的状态(i==arr.size())，只有sum==aim位置为ture，其他位置都为false。
> 5. 回到递归中看普遍状态都受哪些状态的影响。对于f(i,sum) = f(i+1,sum) or f(i+1, sum+arr[i])，在二维表中就是受它正对的下面的元素f(i+1,sum)和它下面一行向右推arr[i]长度的位置的元素f(i+1,sum+arr[i])，他俩或一下就是要求的当前位置的状态。所有可以知道填表的顺序是从下到上，从右到左（或从左到右，但是越界会出问题），注意出来越界问题，当sum+arr[i](sum表示的是列位置)大于总的列数S时就会从dp矩阵中越界，此时只需看f(i+1, sum)来决定f(i,sum)即可。

```c++
bool isSumAimDp(vector<int> arr, int aim)
{
    int S = 0;
    for(int i=0; i<arr.size(); i++)
    {
        S += arr[i];
    }
    if(S<aim) return false;
    int n = arr.size();

    vector<vector<bool>> dp(n+1,vector<bool>(S+1)); // 范围： [0,N], [0,Sum]

    // 对最后一行
    for(int sum=0; sum<=S; sum++)
    {
        if(sum==aim) dp[n][sum] = true;
        else dp[n][sum] = false;
    }

    for(int i=n-1; i>=0; i--)
    {
        for(int sum=0; sum<=S; sum++)
        {
            if(sum+arr[i] <= S)
            {
                dp[i][sum] = (dp[i+1][sum] | dp[i+1][sum+arr[i]]);
            }
            else
            {
                dp[i][sum] = dp[i+1][sum];
            }
        }
    }
    return dp[0][0];
}
```

> 若arr中不都是整数，那么要重新设计一下dp表。比如arr=[3,-2,5]，那么sum就是[-2,-1,0,1,2,3,4,5,6,7,8]，但是对应的列数j还是[0，1，2，3，4，5，6，7，8，9，10]