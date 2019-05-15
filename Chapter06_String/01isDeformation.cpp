#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution{
public:
    bool isDeformation(string str1, string str2)
    {
        if(str1.empty() || str2.empty() || str1.size()!=str2.size()) return false;
        unordered_map<char, int> m;
        for(char c: str1)
        {
            if(m.count(c)==0) m[c]=1;
            else m[c]++;
        }
        for(char c: str2)
        {
            if(m.count(c)==0) return false;
            else
            {
                m[c]--;
                if(m[c]<0) return false;
            }
        }
        return true;
        
    }
};


int main()
{
    Solution s;
    string s1, s2;
    cin >> s1;
    cin >> s2;
    bool res = s.isDeformation(s1, s2);
    cout << res << endl;
    return 0;
}
