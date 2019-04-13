## 随时找到数据流中的中位数
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/MedianHolder.cpp)

**题目：**

> 有一个源源不断地吐出整数的数据流，假设你有足够的空间来保存吐出的数。请设计一个名叫MedianHolder的结构，MedianHolder可以随时取得之前吐出的所有数的中位数
> 
> **要求**：
> 
> 1. 如果MedianHolder已经保存了吐出的N个数，那么任意时刻将一个新数加入到MedianHolder的过程，其时间复杂度为O(log(N))。
> 
> 2. 取得已经吐出的N个数整体的中位数的过程，时间复杂度为O(1)。

> 使用一个大根堆和一个小根堆构建MedianHolder结构。大根堆中含有接收的所有数中的较小的一半，并且按照大根堆的方式组织起来，那么这个堆的堆顶就是较小的一半数中最大的那个。小根堆中含有接收的所有数中较大的一半，并且按照小根堆的方式组织起来，那么这个堆的堆顶就是较大的一半数中最小的那个。若是目前位置的接收的数的个数为偶数个（此时大根堆中元素个数一定等于小根堆中元素个数），那么中位数就是大根堆堆顶与小根堆堆顶相加再除以二。若大根堆中元素个数大于小根堆中元素个数，那么中位数就是大根堆的堆顶，反之亦然。
>
> 对于新来的元素cur，若此时大根堆里没有元素，那么就进大根堆。若大根堆里有元素，那么判断cur与大根堆的堆顶元素的大小，若cur不大于大根堆的堆顶，那么进大根堆。否则，再看cur与小根堆堆顶的大小，若cur不小于小根堆的堆顶，那么进小根堆，否则进大根堆（也就是cur大于大根堆的堆顶但是小于小根堆的堆顶时也进大根堆）。然后根据大小根堆中的元素个数进行调整。若大根堆的size比小根堆的size大2，那么就把大根堆的堆顶弹出放到小根堆里，反之亦然。


> 使用queue库中的优先级队列可直接构建大根堆和小根堆。
> 
> priority_queue用法介绍：
> 需要包含头文件#include<queue>
>
> 定义：priority_queue<Type, Container, Functional>， Type为数据类型，Container为容器的类型（必须是用数组实现的容器，如vector，STL中默认使用vector），functional为比较的方式，当需要用自定义的类型时才需要传入这三个参数，使用基本数据类型时，只需传入数据类型，默认数大根堆。


```c++
//大根堆，降序队列
priority_queue<int, vector<int>, less<int> > MaxHeap;
//小根堆，升序队列
priority_queue<int, vector<int>, greater<int> > MinHeap;
```
> 用法：
> 
> * top() 访问头元素
> 
> * empty() 判断队列是否为空
> 
> * push() 插入一个元素到末尾并排序
> 
> * pop() 弹出队头的元素
> 
> * size() 返回队列内的元素个数
> 
> * emplace() 原地构造一个元素并插入队列
> 
> * swap() 交换内容


```c++
class MedianHolder{
public:
    priority_queue<int, vector<int>, greater<int>> minHeap;
    priority_queue<int, vector<int>, less<int>> maxHeap;
    void add_number(int num);
    double getMedian();
    void modifyHeapSize();
};

void MedianHolder::add_number(int num)
{
    if(maxHeap.empty()) 
    {   
        maxHeap.push(num);
        return;
    }
    if(num<=maxHeap.top())
    {
        maxHeap.push(num);
    }
    else
    {
        if(minHeap.empty()) 
        {
            minHeap.push(num);
            return;
        }
        if(num>=minHeap.top())
        {
            minHeap.push(num);
        }
        else maxHeap.push(num);
    }
    modifyHeapSize();
}
void MedianHolder::modifyHeapSize()
{
    if(maxHeap.size() == minHeap.size()+2) 
    {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
    }
    if(minHeap.size() == maxHeap.size()+2)
    {
        maxHeap.push(minHeap.top());
        minHeap.pop();
    }
}

double MedianHolder::getMedian()
{
    long maxHeapSize = maxHeap.size();
    long minHeapSize = minHeap.size();
    if((maxHeapSize+minHeapSize)==0) return NULL;
    int maxHeapHead = maxHeap.top();
    int minHeapHead = minHeap.top();
    if(((maxHeapSize+minHeapSize)&1)==0)
    {
        return (maxHeapHead+minHeapHead)/2.0;
    }
    else if(maxHeapSize>minHeapSize) return maxHeapHead;
    else return minHeapHead;
}
```