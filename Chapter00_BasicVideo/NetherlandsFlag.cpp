#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

void NetherlandsFlag(vector<int> &arr, int L, int R, int num);
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
        is >> ch;
    }
    int num;
    cin >> num;
    NetherlandsFlag(arr, 0, arr.size()-1, num);
    for(auto w: arr)
    {
        cout << w << ",";
    }
    cout << endl;
    return 0;
}

void NetherlandsFlag(vector<int> &arr, int L, int R, int num)
{
    if(arr.empty() || arr.size()<2 || L==R) return;
    int less = L-1;
    int more = R+1;
    int i = L;
    while(i<more)
    {
        if(arr[i]<num)
        {
            swap(arr, i++, ++less);
        }
        else if(arr[i]>num)
        {
            swap(arr, i, --more);
        }
        else i++;
    }

}

void swap(vector<int> &arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
