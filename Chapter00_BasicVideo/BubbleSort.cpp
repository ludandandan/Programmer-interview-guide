#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

void BubbleSort(vector<int> &arr);
void swap(vector<int> &arr, int i, int j);

int main()
{
    // 1,4,2,6,5,7
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
    BubbleSort(arr);
    for(auto w: arr)
    {
        cout << w << ",";
    }
    cout << endl;
    return 0;
}

void BubbleSort(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    for(int end=arr.size()-1; end>0; end--)
    {
        for(int i=0; i<end; i++)
        {
           if(arr[i]>arr[i+1]) swap(arr, i, i+1); 
        }
    }
}

void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
