#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#define INT_MIN -65536
using namespace std;

class Solution{
public:
    vector<char> ManacherString(string str)
    {
        int n = str.size();
        vector<char> res(2*n+1);
        int i = 0;
        int j = 0;
        while(i<(2*n+1))
        {
            res[i] = (i&1)==0?'#':str[j++];
            i++;
        }
        return res;
    }

    int maxLcpsLength(string str)
    {
        if(str.empty()) return 0;
        if(str.size()==1) return 1;
        vector<char> s = ManacherString(str);
        int n = s.size();
        vector<int> pArr(n, 1); //最长回文半径
        int pR = -1;//最右右边界
        int index = -1;//最右右边界的回文中心
        int max_len = INT_MIN;
        for(int i=1; i<n; i++)
        {
            // i在不在pR里面，最起码的回文半径
            pArr[i] = i<pR ? min(pArr[2*index-i], pR-i):1;
            //看看还能不能往外扩
            while(((i+pArr[i])<n) && ((i-pArr[i])>=0) && (s[i+pArr[i]]==s[i-pArr[i]]))
            {
                pArr[i]++;
            }
            if((i+pArr[i])>pR)
            {
                pR = i+pArr[i];
                index = i;
            }
            max_len = max(max_len, pArr[i]);
        }
        return max_len-1;
    }
    string getLongestPalindromicSubstring(string s)
    {
        string res;
        if(s.empty()) return res;
        if(s.size()==1) return s;

        vector<char> vc = ManacherString(s);
        int n = vc.size();
        int pR = -1;
        int index = -1;
        vector<int> pArr(n, 1);
        int max_index = -1;//保存最长回文子串的回文中心
        int max_len = -1;

        for(int i=1; i<n; i++)
        {
            //根据i是否在pR里面确定最起码的回文半径
            pArr[i] = i<pR ? min(pArr[index*2-i], pR-i):1;
            while(((i-pArr[i])>=0) && ((i+pArr[i])<n) && (vc[i-pArr[i]]==vc[i+pArr[i]]))
            {
                pArr[i]++;
            }
            if((i+pArr[i])>pR)
            {
                pR = i+pArr[i];
                index = i;
            }
            if(max_len<pArr[i])
            {
                max_len = pArr[i];
                max_index = index;
            }
        }
        for(int i=max_index-pArr[max_index]+1; i<(max_index+pArr[max_index]); i++)
        {
            if(vc[i]!='#') res+=vc[i];
        }
        return res;
    }
};

int main()
{
    string str;
    cin >> str;

    Solution s;
    int res = s.maxLcpsLength(str);
    cout << res << endl;
    string s0 = s.getLongestPalindromicSubstring(str);
    cout << s0 << endl;
    return 0;
}

