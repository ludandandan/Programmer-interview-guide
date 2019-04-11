#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int smallSum(vector<int> &arr);
int mergeSort(vector<int> &arr, int L, int R);
int merge(vector<int> &arr, int L, int mid, int R);

int main()
{
    // 1,3,5,2,4,6
    vector<int> arr;
    string line;
    getline(cin, line);
    istringstream is(line);
    int n;
    char ch;
    while(is >> n)
    {
        arr.push_back(n);
        is >> ch;
    }
    int res = smallSum(arr);
    cout << res << endl;
    return 0;
}


int smallSum(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return 0;
    return mergeSort(arr, 0, arr.size()-1);
}

int mergeSort(vector<int> &arr, int L, int R)
{
    if(L==R) return 0;
    int mid = L + ((R-L)>>1);
    return mergeSort(arr, L, mid) + mergeSort(arr, mid+1, R) +
        merge(arr, L, mid, R);
}

int merge(vector<int> &arr, int L, int mid, int R)
{
    vector<int> help(R-L+1);
    int pl = L;
    int pr = mid+1;
    int i = 0;
    int res = 0;
    while(pl<=mid && pr<=R)
    {
        res += arr[pl]<=arr[pr]? arr[pl]*(R-pr+1):0;
        help[i++] = arr[pl]<=arr[pr]? arr[pl++]:arr[pr++];
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
    return res;
}
