## 荷兰国旗问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/NetherlandsFlag.cpp)

**题目：**
> 给定一个数组arr和一个数num，请把大于num的数放在数组的左边，等于num的数放在数组的中间，小于num的数放在数组的右边。要求时间复杂度O(N)，空间复杂度O(1)。

> 使用两个指针less和more分别指想arr的左边界L的前一个(less=L-1)和右边界R的后一个(more=R+1)，表示less及less右边的元素小于num，more及more左边的元素大于num，那么less与more之间的元素就是等于num。将整个数组arr遍历一遍，逐个处理每个元素。假设现在处理的元素cur=arr[i]，若cur<num，那就将cur与less的下一个数(arr[less+1])交换，同时less和i的往前走一个，表示小于区域向右扩一。若cur>num，那么就把cur与more的左边元素(arr[more-1])交换位置，同时将more往左走一个，即大于区域向左扩一，但是此时的i不能往前走，因为换过去的元素还没确定是大于还是小于还是等于，还得再检查。若cur==num，那么就什么都不做，i往前走1，检查下面的元素。当索引i与more撞车了，那么就停。虽然在cur>num时，i不动，但more动了，所以是会撞车的。

```c++
void NetherlandsFlag(vector<int> &arr, int L, int R, int num)
{
    if(arr.empty() || arr.size()<2 || L==R) return;
    int less = L-1;
    int more = R+1;
    int i = L;
    while(i<more)
    {
        if(arr[i]<num)
        {
            swap(arr, i++, ++less);
        }
        else if(arr[i]>num)
        {
            swap(arr, i, --more);
        }
        else i++;
    }

}

void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
```