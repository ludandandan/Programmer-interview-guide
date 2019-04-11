#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
using namespace std;

void InsertSort(vector<int> &arr);
void swap(vector<int> &arr, int i, int j);

int main()
{
    // 5,3,4,0,6
    vector<int> arr;
    string line;
    getline(cin, line);
    int n;
    char ch;
    istringstream is(line);
    while(is>>n)
    {
        arr.push_back(n);
        is >> ch;
    }
    InsertSort(arr);
    for(auto n: arr)
    {
        cout << n << ",";
    }
    cout << endl;
    return 0;
}

void InsertSort(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    for(int i=1; i<arr.size(); i++)
    {
        for(int j=i-1; j>=0&&arr[j]>arr[j+1]; j--)
            swap(arr, j, j+1);
    }
}

void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
