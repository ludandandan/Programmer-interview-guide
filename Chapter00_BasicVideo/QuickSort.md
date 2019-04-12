## 快速排序
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/QuickSort.cpp)

**题目：**
> 随机快排的细节及复杂度分析，数组长度为N。

> 经典快排使用了partition的思想，划分点num固定为数组的最后一个元素。假设数组arr左边界为L，右边界为R。划分数为num=arr[R]，使用partition将arr分为小于等于num区域[L， less]和大于num区域[less+1, R]。同时需保证less位置上放的数为num。然后再分别在这两个区域上重复上述操作，即使用递归，递归的终止条件数L==R，此时只剩一个数无需排序了。

> 经典快排的缺陷，每次只能搞定一个数，即中间等于num的数。若使用荷兰国旗的思想划分为小于，等于，和大于三个区域，递归的时候再操作小于和大于两个区域，整个等于区域都已经搞定了。

> 但是这种排序由于每次的划分数都是最后一个数，受数据状况影响严重。比如数组为[5,4,3,2,1]，每次只使用最后一个数作为划分点就会导致只有大于区域而没有小于区域，时间复杂度会接近$O(N^{2})$，但是若能每次划分点都能使小于区域和大于区域的数一样多，就可以使用master公式估算时间复杂度T(N)=2T(N/2)+O(N)，这样复杂都度为$O(N*log(N))$。为了使排序时间不那么受数据状况的影响，采用随机快排。就是在数组范围L\~R上随机生成一个数i作为索引，将这个数i在数组中对应的数arr[i]与数组的最后一个数arr[R]交换。partition还是使用arr的最后一个数arr[R]作为划分数，partition的返回值为整个等于区域的两个边界值。用于在递归的时候划分，找到小于区域和大于区域。正是由于需要保存这个边界值，随机快排的空间复杂度为O(log(N))，相当于一棵树的高度。
> 
> 使用cstdlib库中的void srand(unsigned int seed)和int rand(void)函数结合生成随机数。首先srand(time(NULL))定义一个与时间有关的种子，以使随机数每次生成的不一样。要生成位于[L,R]范围上的随机数rand()%(R-L+1)+L。

```c++
void QuickSort(vector<int> &arr, int L, int R)
{
    if(L<R)
    {
        vector<int> p = partition(arr, L, R);
        QuickSort(arr, L, p[0]-1);
        QuickSort(arr, p[1]+1, R);
    }
}

vector<int> partition(vector<int> &arr, int L, int R)
{
    srand(time(NULL));
    int rand_index = rand()%(R-L+1)+L; //生成一个[L,R]之间的随机数
    swap(arr, rand_index, R); //始终使用最后一个数作为num进行划分
    int less = L-1;
    int more = R+1;
    int i = L;
    while(i<more)
    {
        if(arr[i]<arr[R]) swap(arr, i++, ++less);
        else if(arr[i]>arr[R]) swap(arr, i, --more);
        else i++;
    }
    vector<int> p;
    p.push_back(++less);
    p.push_back(--more);
    return p;
}

void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

```