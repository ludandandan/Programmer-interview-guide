#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution{
public:
    int getIndex(vector<string> &strs, string str)
    {
        if(strs.empty() || str.empty()) return -1;
        int n = strs.size();
        int l = 0;
        int r = n-1;
        int mid = 0;
        int res = -1;//一开始必须为-1，因为若是下面的while找不到就会返回初始值-1
        while(l<=r)
        {
            mid = l + (r-l)/2;
            //若中间正好是str，为了取得最左，再向左半边查找
            if(strs[mid]==str)
            {
                res = mid;
                r = mid-1;
            }
            //若mid不是空
            else if(strs[mid]!="")
            {
                //若mid比str小，那么检查右半边
                if(strs[mid]<str) l = mid+1;
                else r = mid-1;
            }
            else //若Mid是空的
            {
                //先检查左半边l,...,mid-1，从右向左，直到一个不为空的位置
                int i = mid-1;
                while(i>=l)
                {
                    if(strs[i]!="") break;
                    else i--;
                }
                if(i<l || strs[i]<str) l = mid+1;
                else if(strs[i]==str)
                {
                    res = i;
                    r = i-1;
                }
                else r = i-1;
            }
        }
        return res;
    }
};


int main()
{
    string str="d";
    vector<string> strs= {"", "a", "", "a", "", "b", "", "c", ""};
     Solution s;
     int res = s.getIndex(strs, str);
    cout << res << endl;

    return 0;
}



