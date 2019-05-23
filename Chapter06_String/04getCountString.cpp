#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution{
public:
    string getCountString(string s)
    {
        string res;
        if(s.empty()) return res;
        int count = 1;
        int i = 1;
        int n = s.size();
        res = s[0];
        while(i<n)
        {
            if(s[i]==s[i-1]) count++;
            else
            {
                char c = count+'0';
                res = res + '_' +  c + '_' + s[i];
                count = 1;
            }
            i++;
        }
        char lc = count + '0';
        res = res + '_' + lc;
        return res;
    }
};


int main()
{
    Solution s;
    string str;
    cin >> str;
    string res = s.getCountString(str);
    cout << res << endl;
    return 0;
}
