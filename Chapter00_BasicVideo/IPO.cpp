#include <cstdio>
#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

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

int main()
{
    vector<int> costArr{0,1,1};
    vector<int> profitArr{1,2,3};
    int w = 0;
    int k = 2;
    int res = findMaximizedCapital(costArr, profitArr, w, k);
    cout << res << endl;
    return 0;
}
