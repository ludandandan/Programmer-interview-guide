#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

void printReverseOrderPair(vector<int> &arr);
void mergeSort(vector<int> &arr, int L, int R);
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
    printReverseOrderPair(arr);
    cout << endl;
    return 0;
}

void printReverseOrderPair(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    mergeSort(arr, 0, arr.size()-1);
}

void mergeSort(vector<int> &arr, int L, int R)
{
    if(L==R) return;
    int mid = L + ((R-L)>>1);
    mergeSort(arr, L, mid);
    mergeSort(arr, mid+1, R);
    merge(arr, L, mid, R);
}

void merge(vector<int> &arr, int L, int mid, int R)
{
    vector<int> help(R-L+1);
    int pl = L;
    int pr = mid+1;
    int i = 0;
    while(pl<=mid && pr<=R)
    {
        if(arr[pr]<arr[pl])
        {
            int j = pl;
            while(j<=mid)
            {
                cout << '(' << arr[j++] << ',' << arr[pr] << ')';
            }
        }
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
        arr[L+i] = help[i];
    }
}
