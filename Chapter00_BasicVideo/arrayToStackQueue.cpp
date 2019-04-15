#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class ArrayToStack{
public:
    vector<int> arr;
    int index;
    ArrayToStack(int initSize): arr(vector<int>(initSize)), index(0) {}
    /*
    void init(int initSize)
    {
        if(initSize<0)
        throw runtime_error("the init size is less than 0!");
        vector<int> tmp(initSize);
        arr = tmp;
    }
    */
    void push(int num)
    {
        if(index==arr.size()) throw runtime_error("the stack is full!");
        arr[index++] = num;
    }
    
    int pop()
    {
        if(index==0) throw runtime_error("the stack is empty!");
        return arr[--index]; 
    }

    int top()
    {
        if(index==0) return NULL;
        return arr[index-1];
    }
};

class ArrayToQueue{
public:
    vector<int> arr;
    int end;
    int start;
    int size;
    ArrayToQueue(int initSize): arr(vector<int>(initSize)), end(0), start(0), size(0){}

    void push(int num)
    {
        if(size==arr.size()) throw runtime_error("the queue is full!");
        arr[end] = num;
        end = end==arr.size()-1?0:end+1;
        size++;
    }
    int pop()
    {
        if(size==0) throw runtime_error("the queue is empty!");
        int tmp = arr[start];
        start = start==arr.size()-1?0:start+1;
        size--;
        return tmp;
    }
    int top()
    {
        if(size==0) return NULL;
        return arr[start];
    }

};
int main()
{
    cout << "stack test: " << endl;
    ArrayToStack s(4);
    s.push(1);
    s.push(2);
    s.push(3);
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    
    cout << "queue test: " << endl;
    ArrayToQueue q(4);
    q.push(1);
    q.push(2);
    q.push(3);
    cout << q.top() << endl;
    q.pop();
    cout << q.top() << endl;
    q.pop();
    cout << q.top() << endl;
    q.pop();
    cout << q.top() << endl;
    q.pop();
    return 0;
}
