#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int getMax(vector<int> &arr, int L, int R);

int main()
{
    vector<int> arr;
    string line;
    getline(cin,line);
    istringstream is(line);
    int n;
    char ch;
    while(is>>n)
    {
        arr.push_back(n);
        is >> ch;
    }
    int res = getMax(arr, 0, arr.size()-1);
    cout << res << endl;
    return 0;
}

int getMax(vector<int> &arr, int L, int R)
{
    if(L==R) return arr[L];
    int mid = L + (R-L)/2;
    int maxL = getMax(arr, L, mid);
    int maxR = getMax(arr, mid+1, R);
    return max(maxL, maxR);
}
