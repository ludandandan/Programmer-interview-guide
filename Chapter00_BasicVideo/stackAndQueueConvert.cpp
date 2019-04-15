#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

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
int main()
{
    cout << "new stack: " << endl;
    TwoQueueStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << s.top() << endl;//3
    s.pop();
    s.push(4);
    cout << s.top() << endl;//4
    s.pop();
    cout << s.top() << endl;//2
    s.pop();
    cout << s.top() << endl; //1
    s.pop();

    cout << "new queue: " << endl;
    TwoStackQueue q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << q.front() << endl; //1
    q.pop();
    q.push(4);
    cout << q.front() << endl; //2
    q.pop();
    cout << q.front() << endl; //3
    q.pop();
    cout << q.front() << endl; //4
    q.pop();
    return 0;

}
