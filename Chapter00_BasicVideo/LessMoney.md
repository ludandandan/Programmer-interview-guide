## 分金条问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/LessMoney.cpp)

**题目：**
> 一块金条分为两半是要花费和长度数值一样的铜板的。比如长度为20的金条，不管切成长度多大的两半，都要花费20个铜板。一群人想要分整块金条，怎么分最省铜板？
> 例如给定数组{10,20,30}，代表一共三个人，每个人的诉求分别是10，20和30，金条的总长度为10+20+30=60。金条要分为10，20和30三部分。如果先把长度为60的金条分为10和50，花费60个铜板，再把长度为50的金条分为20和30花费50个铜板，总共花费60+50=110个铜板。但是如果先把长度为60的金条分为30和30，花费60个铜板，再把长度为30的金条分为10和20花费30个铜板，总共花费30+60=90个铜板。
> 
> 输入一个数组，返回分割的最小代价。

>哈夫曼编码：最终要使用所有的叶节点生成一棵树，两个叶节点结合的代价为他们的和，生成树后所有非叶节点加起来就是总代价。
> 首先将数组里的数都放到一个小根堆里去。每次从小根堆里取出两个最小的（也就是堆顶元素），将这两个节点结合，并将结合的代价（这里是两个节点的和，根据不同的题目可能是乘或其他计算公式）放回到小根堆里，然后再从小根堆里取出两个最小的来继续上面操作。直到小根堆里只剩下一个数停止。总的代价就是每步产生的代价之和。
> 
> 小根堆可以帮助完成这一过程，通过定义不同的比较器可以定义不同的堆，小根堆每次取出两个最小的，从底向上逆向操作，实际切割时是从上向下的操作。
> 
> 什么时候可以尝试使用哈夫曼编码贪心？
> 当总的代价是子代价的累加/乘/或其他时，可以尝试哈夫曼。

```c++
int lessMoney(vector<int> arr)
{
    if(arr.empty()) return 0;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for(int n: arr)
    {
        minHeap.push(n);
    }
    int res = 0;
    while(minHeap.size()>1)
    {
        int min1 = minHeap.top();
        minHeap.pop();
        int min2 = minHeap.top();
        minHeap.pop();
        int m = min1+min2;
        res += m;
        minHeap.push(m);
    }
    return res;
}
```