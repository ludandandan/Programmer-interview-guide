#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
using namespace std;

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

int main()
{
    myStack s;
    s.push(5);
    s.push(4);
    s.push(3);
    s.push(6);
    cout << s.top() << endl;
    cout << "getMin:" << endl;
    cout << s.getMin() << endl;
    s.pop();
    s.pop();
    cout << s.getMin() << endl;
    
}
