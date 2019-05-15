#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define INT_MIN -65536
#define INT_MAX 65535
using namespace std;

class Solution{
public:
    int myatoi(string s)
    {
        if(s.empty()) return 0;
        int n = s.size();
        int k = 0;
        int sign = 1;
        int res = 0;
        while(s[k]==' ') k++;
        if(s[k]=='+') k++;
        else if(s[k]=='-')
        {
            sign = -1;
            k++;
        }
        for(; k<n; k++)
        {
            if(s[k]<'0' || s[k]>'9')
            {
                return res*sign;
            }
            else
            {
                int a = s[k]-'0';
                if(res>INT_MAX/10 || ((res==INT_MAX/10) && (a>(INT_MAX-res*10))))
                {
                    return sign==1?INT_MAX:INT_MIN;
                }
                else res = res*10+a;
            }
        }
        return res*sign;
    }
};


int main()
{
    Solution s;
    string str;
    cin >> str;
    int res = s.myatoi(str);
    cout << res << endl;
    return 0;
}
