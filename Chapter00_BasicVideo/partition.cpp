#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
using namespace std;

void partition(vector<int> &arr, int num);
void swap(vector<int> &arr, int i, int j);
int main()
{
    //4,5,67,8,4,1,3,1,0,9
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
    int num;
    cin >> num;
    partition(arr, num);
    for(auto w: arr)
    {
        cout << w << ",";
    }
    cout << endl;
    return 0;
}

void partition(vector<int> &arr, int num)
{
    if(arr.empty() || arr.size()<2) return;
    int less = -1;
    for(int i=0; i<arr.size(); i++)
    {
        if(arr[i]<=num)
        {
            swap(arr, i, ++less);
        }
    }
}

void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
