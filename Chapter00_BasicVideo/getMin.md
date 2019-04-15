## 设计一个有getMin功能的栈
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/getMin.cpp)

**题目：**
> 实现一个特殊的栈，在实现栈功能的基础上，再实现返回栈中最小元素的操作
> 
> 要求：
> 1. pop, push, getMin操作的时间复杂度都是O(1).
> 2. 设计的栈类型可以使用现成的栈结构。

> 使用两个现成的栈结构，一个叫dataStack，一个叫minStack。dataStack用于正常存数据，minStack用于保证实现getMin功能。
> 1. 对于push功能：当用户向栈中加入一个数num时，num先被Push到dataStack中，然后看看minStack中是否为空，如果是空的话直接将这个数num也push到minStack中，否则就看看num与minStack的栈顶哪个比较小，把较小的那个push进minStack。
> 2. 对于pop功能：当用户需要弹出一个数时，将dataStack的栈顶弹出，同时将minStack的栈顶也弹出。
> 3. 对于getMin功能：当前minStack的栈顶就是当前dataStack栈中所有元素的最小值。
> 4. 对于top功能：直接使用dataStack的top即可。

```c++
class myStack{
private:
    stack<int> dataStack;
    stack<int> minStack;
public:
    void push(int num)
    {
        dataStack.push(num);
        if(minStack.empty()) minStack.push(num);
        else
        {
            if(minStack.top()<num) minStack.push(minStack.top());
            else minStack.push(num);
        }
    }
    void pop()
    {
        if(dataStack.empty()) throw runtime_error("the stack is empty!");
        minStack.pop();
        dataStack.pop();
    }
    int top()
    {
        return dataStack.top();
    }
    int getMin()
    {
        if(dataStack.empty()) throw runtime_error("the stack is empty!");
        return minStack.top();
    }
};

```