#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
#define INT_MIN -65535
#define INT_MAX 65535
 
//排序之后从两头开始加
int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
 
    sort(arr.begin(), arr.end());
    int max_val = INT_MIN;
    int min_val = INT_MAX;
    for (int i = 0; i < n / 2; i++)
    {
        int val = arr[i] + arr[n - i - 1];
        max_val = max(max_val, val);
        min_val = min(min_val, val);
    }
    int gap = max_val - min_val;
    cout << gap << endl;
    getchar();
    return 0;
}