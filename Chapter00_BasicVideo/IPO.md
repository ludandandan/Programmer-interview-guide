## IPO问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/IPO.cpp)

**题目：**
> 详细题目可见[leetCode502IPO](https://leetcode.com/problems/ipo/)
> 有两个数组，cost数组和profit数组分别代表做项目的花费和利润，cost[i]和profit[i]表示做第i个项目的花费和利润。给定一个启动金额w，用这个启动金去做项目，可以做所有花费小于等于w的项目，每次只能做一个项目，做完一个项目后会获得相应的利润，然后可以去做别的可以做的项目，总共最多可以做k个项目。求最终可获得的最多的钱数是多少。

> 建立一个数据结构Node来表示一个项目，每个node有两个数据变量cost和profit。然后准备一个小根堆将这些项目全部放进去，这个小根堆根据cost小的放在顶上排列。这个小根堆表示所有的项目。然后准备一个大根堆，大根堆根据profit高的放在顶上排列。看初始基金w，从小根堆里依次弹出头来放到大根堆里（在小根堆不为空的情况下），只要这个头的cost小于等于当前手里的钱数（也就是凭当前的钱数可以做）。所以大根堆里放的是凭当前手里的钱可以解锁的项目。然后从大根堆的顶部取出一个项目来做掉（这个项目是所有可以做的项目里收益最大的），然后更新当前手里的钱数w，也就是在原来基础上加上刚做完的项目的profit，然后再看小根堆里有没有新的项目可以解锁（在小根堆不为空的情况下），有就从小根堆弹出放到大根堆里。直到做完k个项目或者大根堆里的为空了就停止。

```c++
struct Node{
    int cost;
    int profit;
    Node(int c, int p):cost(c),profit(p){}
};

struct costGreater{ //花费小根堆
    bool operator() (Node *o1, Node *o2)
    {
       return (o1->cost) > (o2->cost);
    }
};

struct profitLess{ //收益大根堆
    bool operator() (Node *o1, Node *o2)
    {
        return (o1->profit) < (o2->profit);
    }
};

int findMaximizedCapital(vector<int> costArr, vector<int> profitArr, int w, int k)
{
    if(costArr.empty() || profitArr.empty()) return 0;
    priority_queue<Node*, vector<Node*>, costGreater> costMin;
    priority_queue<Node*, vector<Node*>, profitLess> profitMax;
    int n = costArr.size();
    for(int i=0; i<n; i++)
    {
        Node *node = new Node(costArr[i], profitArr[i]);
        costMin.push(node);
    }
    while(!costMin.empty() && w>=costMin.top()->cost)
    {
        Node *node = costMin.top();
        costMin.pop();
        profitMax.push(node);
    }
    while(k!=0 && !profitMax.empty())
    {
        Node *node = profitMax.top();
        profitMax.pop();
        k--;
        w += node->profit;
        while(!costMin.empty() && w>=costMin.top()->cost)
        {
            profitMax.push(costMin.top());
            costMin.pop();
        }
    }
    return w;
}
```