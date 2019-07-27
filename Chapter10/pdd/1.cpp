#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#define INT_MIN -65535
#define INT_MAX 65535
using namespace std;
//最大乘积
int main()
{
    long long n, num;
    cin >> n;
    //定义最大值，次大值，第三大的值，和最小值，次小值
    long long max1 = INT_MIN;
    long long max2 = INT_MIN;
    long long max3 = INT_MIN;
    long long min1 = INT_MAX;
    long long min2 = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        if (num < min1)
        {
            min2 = min1;
            min1 = num;
        }
        else if (num < min2)
        {
            min2 = num;
        }
 
        if (num > max1)
        {
            max3 = max2;
            max2 = max1;
            max1 = num;
        }
        else if (num > max2)
        {
            max3 = max2;
            max2 = num;
        }
        else if (num > max3)
        {
            max3 = num;
        }  
    }
    if (max1*max2*max3 > max1*min1*min2)
    {
        cout << max1 * max2*max3 << endl;
    }
    else cout << max1 * min1*min2 << endl; 
    return 0;
}