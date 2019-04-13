## 堆排序
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/HeapSort.cpp)

**题目：**

> 堆排序的细节及复杂度分析。数组长度N。

> 堆结构实际上是一棵完全二叉树，可以使用数组来实现。数组arr的第i个元素arr[i]的父节点为arr[(i-1)/2]，左孩子为arr[i\*2+1]，右孩子为arr[i\*2+2]。堆分为大根堆和小根堆，大根堆中任意子树中的最大值为其头节点，小根堆中任意子树中的最小值为其头节点。

> 数组进行堆排序的步骤：
> 
>   1.整个数组建立一个大根堆（应用heapInsert操作）
>
>   2.经过步骤一之后整个数组上的最大值被放在了大根堆的堆顶，将堆顶与最后一个元素交换，同时标记越界的heapSize减一。这样最大数就被沉的了数组最后，搞定一个数。
>
>   3.然后heapify操作将大小为heapSize的数组arr[0,...,heapSize-1]重新调整为大根堆。重复步骤二（即将堆顶的数与最后一个数交换）
>
>   4.重复步骤二和三，直到heapSize变为0，整个数组排序完毕。

> 时间复杂度分析：
> 
>   1.建立一个大根堆的时间复杂度为O(N) = log1+log2+..+log(N-1)；大根堆是逐渐建立起来的，先0\~0构成大根堆，然后插入1元素在0\~1上构成大根堆，然后插入i...，在一棵节点数为N-1的完全二叉树（已经构成大根堆）中插入一个节点N向下调整为新的大根堆的时间为log(N-1)。
> 
>   2.将一个在有N个节点的大根堆中的元素从堆顶开始heapify调整的时间复杂度为log(N)，逐个调整N个元素（每次只搞定最大的元素）时间复杂度为O(Nlog(N))。
>   3.去掉低阶项后堆排序的时间复杂度O(Nlog(N))。

> 建立大根堆heapInsert：
>
> 假设arr[0,...,i-1]上已经构成大根堆，新插入元素arr[i]，那么找到i的父节点(i-1)/2，若arr[i]父节点上数arr[(i-1)/2]大，则arr[i]与其父节点交换位置，同时i变为其父节点处的索引，继续上述过程，直到不比其父节点大了。(0的父节点还是0,(0-1)/2=0).

> heapify(某个数组里面的某个元素变小了，如何重新调整成大根堆。)：
>
> 将变小的元素向下沉。假设arr[i]变小了，先找到arr[i]的两个孩子arr[i*2+1]和arr[i*2+2]，比较两个孩子找到较大的那个largest，若两个孩子不存在，那么arr[i]是叶节点了，无需再调整，若只有左孩子，那就让左孩子i*2+1等于largest。然后比较arr[i]与arr[largest]大小，若arr[i]不比arr[largest]大也无需调整，否则就将arr[largest]与arr[i]交换，直到arr[i]不比他的孩子小了或者他没有孩子了就停。


```c++
void heapSort(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    //整个数组建立大根堆
    for(int i=0; i<arr.size(); i++)
    {
        heapInsert(arr, i);
    }
    //逐个搞定最大元素，即将其放到最后
    int heapSize = arr.size();
    while(heapSize>0)
    {
        swap(arr, 0, --heapSize);
        heapify(arr, 0, heapSize);
    }
}
// [0,index-1]位置已经是大根堆了，然后进来数arr[index]将[0,index]变为大根堆
void heapInsert(vector<int> &arr, int index)
{
    //找到父节点,向上调整建立大根堆
    while(arr[index]>arr[(index-1)/2])
    {
        swap(arr, index, (index-1)/2);
        index = (index-1)/2;
    }
}

//向下调整
void heapify(vector<int> &arr, int index, int heapSize)
{
    int left = index*2+1;
    while(left < heapSize)
    {
        int largest = (left+1<heapSize) && (arr[left]<arr[left+1])? left+1:left;
        largest = arr[largest]>arr[index]?largest:index;
        if(largest==index) break;
        swap(arr, largest, index);
        index = largest;
        left = index*2+1;
    }
}
void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

```
