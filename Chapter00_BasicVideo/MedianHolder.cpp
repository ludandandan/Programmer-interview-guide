#include <cstdio>
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

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
int main()
{
    MedianHolder mh;
    int n;
    while(cin>>n)
    {
        mh.add_number(n);
    }
    cout << mh.getMedian() << endl;
    return 0;
}
