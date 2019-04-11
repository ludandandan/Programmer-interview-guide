#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

void SelectionSort(vector<int> &arr);
void swap(vector<int> &arr, int i, int j);

int main()
{
    // 2,3,51,5,6,32,1,0
    string line;
    getline(cin, line);
    istringstream is(line);
    vector<int> arr;
    int n;
    char ch;
    while(is>>n)
    {
        arr.push_back(n);
        is>>ch;
    }
    SelectionSort(arr);
    for(auto w: arr)
    {
        cout << w << ",";
    }
    cout << endl;
    return 0;
}

void SelectionSort(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return;
    for(int i=0; i<arr.size()-1; i++)
    {
        int min_index = i;
        for(int j=i+1; j<arr.size(); j++)
        {
            min_index = arr[min_index]>arr[j]?j:min_index;
        }
        swap(arr, i, min_index);
    }
}

void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
