#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

int lessMoney(vector<int> arr);

int main()
{
    vector<int> arr{10,20,30};
    int res = lessMoney(arr);
    cout << res << endl;

    return 0;
}

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
