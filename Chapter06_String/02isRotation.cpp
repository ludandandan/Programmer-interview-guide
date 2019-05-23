#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution{
public:
    bool isRotation(string str1, string str2)
    {
        if(str1.empty() || str2.empty() || str1.size()!=str2.size()) return false;
        string com = str2+str2;
        if(com.find(str1)!=string::npos) return true;
        else return false;
    }
};

int main()
{
    Solution s;
    string str1, str2;
    cin >> str1;
    cin >> str2;
    bool res = s.isRotation(str1, str2); 
    cout << res << endl;
    return 0;
}
