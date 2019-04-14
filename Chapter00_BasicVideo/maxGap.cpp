#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#define INT_MIN -65535
#define INT_MAX 65535
using namespace std;

int maxGap(vector<int> &arr);
int bucket(int len, int max, int min, int num);

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
        is>>ch;
    }
    int res = maxGap(arr);
    cout << res << endl;
    return 0;
}

int maxGap(vector<int> &arr)
{
    if(arr.empty() || arr.size()<2) return 0;
    int len = arr.size();
    vector<bool> hasNumber(len+1, false);
    vector<int> maxNumber(len+1, 0);
    vector<int> minNumber(len+1, 0);
    int max_num = INT_MIN;
    int min_num = INT_MAX;

    for(int i=0; i<len; i++)
    {
        max_num = max(max_num, arr[i]);
        min_num = min(min_num, arr[i]);
    }
    if(max_num==min_num) return 0;
    for(int i=0; i<len; i++)
    {
        int bid = bucket(len, max_num, min_num, arr[i]);
        maxNumber[bid] = hasNumber[bid]?max(maxNumber[bid], arr[i]):arr[i];
        minNumber[bid] = hasNumber[bid]?min(minNumber[bid], arr[i]):arr[i];
        hasNumber[bid] = true;//这个一定要放在max或min有数了之后再变为true，而不能在循环一开始就变为true
    }

    int res = INT_MIN;
    int lastMax = maxNumber[0]; //第一个桶里肯定有数
    for(int i=1; i<=len; i++)
    {
        if(hasNumber[i])
        {
            res = max(res, minNumber[i]-lastMax);
            lastMax = maxNumber[i];
        }
    }
    return res;

}

int bucket(int len, int max, int min, int num)
{
    return (num-min)*len/(max-min);
}
