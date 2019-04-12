#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <cstdlib>
using namespace std;

void QuickSort(vector<int> &arr, int L, int R);
vector<int> partition(vector<int> &arr, int L, int R);
void swap(vector<int> &arr, int i, int j);

int main()
{
    string line;
    getline(cin, line);
    vector<int> arr;
    istringstream is(line);
    int n;
    char ch;
    while(is>>n)
    {
        arr.push_back(n);
        is >> ch;
    }
    QuickSort(arr, 0, arr.size()-1);
    for(auto w: arr)
    {
        cout << w << ",";
    }
    cout << endl;
    return 0;
}

void QuickSort(vector<int> &arr, int L, int R)
{
    if(L<R)
    {
        vector<int> p = partition(arr, L, R);
        QuickSort(arr, L, p[0]-1);
        QuickSort(arr, p[1]+1, R);
    }
}

vector<int> partition(vector<int> &arr, int L, int R)
{
    srand(time(NULL));
    int rand_index = rand()%(R-L+1)+L; //生成一个[L,R]之间的随机数
    swap(arr, rand_index, R); //始终使用最后一个数作为num进行划分
    int less = L-1;
    int more = R+1;
    int i = L;
    while(i<more)
    {
        if(arr[i]<arr[R]) swap(arr, i++, ++less);
        else if(arr[i]>arr[R]) swap(arr, i, --more);
        else i++;
    }
    vector<int> p;
    p.push_back(++less);
    p.push_back(--more);
    return p;
}

void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
