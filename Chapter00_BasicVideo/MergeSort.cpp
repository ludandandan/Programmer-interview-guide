#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

void MergeSort(vector<int> &arr);
void sortProcess(vector<int> &arr, int L, int R);
void merge(vector<int> &arr, int L, int mid, int R);

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
        is >> ch;
    }
    MergeSort(arr);
    for(auto w: arr)
    {
        cout << w << ",";
    }
    cout << endl;
    return 0;
}

void MergeSort(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    sortProcess(arr, 0, arr.size()-1);
}

void sortProcess(vector<int> &arr, int L, int R)
{
    if(L==R) return; //只剩一个数，无需排序了。返回上一层递归进行Merge操作
    int mid = L+((R-L)>>1);
    sortProcess(arr, L, mid);
    sortProcess(arr, mid+1, R);
    merge(arr, L, mid, R);
}

void merge(vector<int> &arr, int L, int mid, int R)
{
    vector<int> help(R-L+1);
    int pl = L;//指向左边的第一个数
    int pr = mid+1;//指向右边的第一个数
    int i = 0;//指向help数组的第一个数
    while(pl<=mid && pr<=R)
    {
        help[i++] = arr[pl]<arr[pr]?arr[pl++]:arr[pr++];
    }
    while(pl<=mid)
    {
        help[i++] = arr[pl++];
    }
    while(pr<=R)
    {
        help[i++] = arr[pr++];
    }
    for(int i=0; i<help.size(); i++)
    {
        arr[i+L] = help[i];
    }
}
