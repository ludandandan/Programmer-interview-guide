#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#define INT_MIN -65535
using namespace std;

class Solution{
public:
    int aimMaxLength(vector<int> arr, int aim)
    {
        if(arr.empty() || arr.size()==0) return 0;
        int L = 0;
        int R = 0;
        int maxLen = INT_MIN;
        int sum = arr[0];
        while(R!=arr.size())
        {
            if(sum==aim)
            {
                maxLen = max(maxLen, R-L+1);
                sum += arr[++R];
            }
            else if(sum<aim)
            {
                sum += arr[++R];
            }
            else
            {
                sum -= arr[L++];
            }
        }
        return maxLen;
    }
};

int main()
{
    vector<int> arr{1,2,5,1,1,1};
    int aim = 3;
    Solution s;
    int res = s.aimMaxLength(arr, aim);
    cout << res << endl;
    return 0;
}
