#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution{
public:
    int strStr(string str, string match)
    {
        if(match.size()==0) return 0;
        if(str.empty() || str.size()<match.size()) return -1;
        if(str.size()==match.size()) return str==match?0:-1;
        vector<int> next = getNext(match);

        int i = 0;
        int j = 0;
        int n1 = str.size();
        int n2 = match.size();
        while(i<n1 && j<n2)
        {
            if(str[i]==match[j]) 
            {
                i++;
                j++;
            }
            else if(next[j]==-1)
            {
                i++;
            }
            else
            {
                j = next[j];
            }
        }
        return j==match.size()?i-j:-1;
    }

    vector<int> getNext(string match)
    {
        vector<int> next(match.size(), 0);
        next[0] = -1;
        if(match.size()==1) return next;
        next[1] = 0;
        if(match.size()==2) return next;
        int pos = 2;
        int cn = next[pos-1];
        while(pos<match.size())
        {
            if(match[pos-1] == match[cn])
            {
                next[pos++] = ++cn;
            }
            else if(cn>0)
            {
                cn = next[cn];
            }
            else
            {
                next[pos++] = 0;
            }
        }
        return next;
    }
};


int main()
{
    string str, match;
    cin >> str;
    cin >> match;
    Solution s;
    int n = s.strStr(str, match);
    cout << n << endl;
    return 0;
}
