## 使用队列结构实现栈 & 使用栈结构实现队列
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/stackAndQueueConvert.cpp)

**题目：**
> 1. 请用队列结构实现栈。
> 2. 请用栈结构实现队列。

> 队列结构实现栈：
>
> 队列结构是先进先出，栈结构是先进后出。假设有一个数序列1,2,3,4,5依次进入队列，则出来的顺序是1,2,3,4,5，而我们希望出来的顺序是5,4,3,2,1。
> 1. 准备两个队列：data队列和help队列。
> 2. 当用户要压入数据时，直接往data队列中压入数据。
> 3. 如果用户要弹出数据，那么先把data队列的前N-1个数(1,2,3,4)放到help队列中，再把最后一个数从data队列中弹出，然后将data队列与help队列交换。
> 4. 如果用户要看栈顶的数据，那么先把data队列的前N-1个数放到help队列中，再把data队列的顶拿出来保存起来为res并给用户看，同时data队列要弹出这个数，然后data队列与help队列交换，然后将res再压入data队列。

> 栈结构实现队列：
> 
> 栈的结构时先进后出，队列是先进先出。假设有一个数序列1,2,3,4依次进入栈，则出来的顺序是4,3,2,1，而我们希望出来的顺序是1,2,3,4。那么可以先让1,2,3,4进入1号栈，然后将1号栈的数全部倒到2号栈，数据从1号栈出来进2号栈的顺序是4,3,2,1，那么从2号栈出来的顺序就是1,2,3,4。这样就达到了目的。
> 1. 准备两个栈：push栈和pop栈。
> 2. 用户要向队列中加入新数据，就进push栈。用户要从队列中取出数据，就从pop栈中取。
> 3. 倒数据必须满足两个要求：一是如果pop栈中有数据就不能往里到；二是push栈决定往pop栈中倒数据了就要一次倒完。

``` c++
class TwoQueueStack{
private:
    queue<int> dataQueue;
    queue<int> helpQueue;
   /* void myswap()
    {
        queue<int> tmp = dataQueue;
        dataQueue = helpQueue;
        helpQueue = tmp;
    }
    */
public:
    void push(int num)
    {
        dataQueue.push(num);
    }
    void pop()
    {
        if(dataQueue.empty()) throw runtime_error("the stack is empty!");
        while(dataQueue.size()>1)
        {
            helpQueue.push(dataQueue.front());
            dataQueue.pop();
        }
        dataQueue.pop();
        swap(dataQueue, helpQueue);
    }
    int top()
    {
        if(dataQueue.empty()) throw runtime_error("the stack is empty!");
        while(dataQueue.size()>1)
        {
            helpQueue.push(dataQueue.front());
            dataQueue.pop();
        }
        int res = dataQueue.front();
        dataQueue.pop();
        swap(dataQueue, helpQueue);
        dataQueue.push(res);
        return res;
    }
};

class TwoStackQueue{
private:
    stack<int> pushStack;
    stack<int> popStack;
    void pullData()
    {
        if(!popStack.empty()) return;
        while(!pushStack.empty())
        {
            popStack.push(pushStack.top());
            pushStack.pop();
        }
    }
public:
    void push(int num)
    {
        pushStack.push(num);
    }
    void pop()
    {
        if(pushStack.empty() && popStack.empty()) throw runtime_error("the queue is empty!");
        pullData();
        popStack.pop();
    }
    int front()
    {
        if(pushStack.empty() && popStack.empty()) throw runtime_error("the queue is empty!");
        pullData();
        return popStack.top();
    }
};
```