## 用数组结构实现大小固定的队列和栈
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/arrayToStackQueue.cpp)

**题目：**
> 用一个长度为N的数组arr，如何实现队列或栈（push, pop, top），push超出N个数报错，pop超出N个数就报错。

> 构建栈：
>   定义一个变量index， 开始时等于0，表示指向arr[0]，index表示如果用户新加一个数，就把这个数放在index位置，同时index++, 如果用户想要弹出一个数，就把--index处的数给用户，如果用户想要得到栈顶就把index-1的数给用户，此时index不变。

> 构建队列：
>   定义三个变量：end, start，和size。这三个变量初始值都是0。end表示若用户想要新加一个数到队列，那么就把它放在end的位置，同时end++(若end到了数组的最后一个元素，那么end再等于0，循环使用数组)。start表示若用户想要弹出一个数，那么就把start位置的数拿出来给用户，同时start++（若start到了数组的最后一个元素，那么start又等于0，重复使用数组）。size用于约束end和start的行为。若size=N了， 用户还想往里加数就报错，若size=0了，用户还想往外弹出数就报错。

```c++
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
```

