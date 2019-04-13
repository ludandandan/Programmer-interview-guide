#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

void heapSort(vector<int> &arr);
void heapInsert(vector<int> &arr, int index);
void heapify(vector<int> &arr, int index, int heapSize);
void swap(vector<int> &arr, int i, int j);

int main()
{
    vector<int> arr;
    string line;
    getline(cin, line);
    istringstream is(line);
    int n;
    char ch;
    while(is>>n)
    {
        arr.push_back(n);
        is>>ch;
    }
    heapSort(arr);
    for(auto m: arr)
    {
        cout << m << ",";
    }
    cout << endl;
    return 0;
}
void heapSort(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    //整个数组建立大根堆
    for(int i=0; i<arr.size(); i++)
    {
        heapInsert(arr, i);
    }
    //逐个搞定最大元素，即将其放到最后
    int heapSize = arr.size();
    while(heapSize>0)
    {
        swap(arr, 0, --heapSize);
        heapify(arr, 0, heapSize);
    }
}
// [0,index-1]位置已经是大根堆了，然后进来数arr[index]将[0,index]变为大根堆
void heapInsert(vector<int> &arr, int index)
{
    //找到父节点,向上调整建立大根堆
    while(arr[index]>arr[(index-1)/2])
    {
        swap(arr, index, (index-1)/2);
        index = (index-1)/2;
    }
}

//向下调整
void heapify(vector<int> &arr, int index, int heapSize)
{
    int left = index*2+1;
    while(left < heapSize)
    {
        int largest = (left+1<heapSize) && (arr[left]<arr[left+1])? left+1:left;
        largest = arr[largest]>arr[index]?largest:index;
        if(largest==index) break;
        swap(arr, largest, index);
        index = largest;
        left = index*2+1;
    }
}
void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
