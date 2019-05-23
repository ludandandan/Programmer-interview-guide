#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution{
public:
    bool sameTypeSameNumber(string str1, string str2)
    {
        if(str1.empty() && str2.empty()) return true;
        if(str1.empty() || str2.empty()) return false;
        if(str1.size()!=str2.size()) return false;
        int n = str1.size();
        unordered_map<char, int> map;
        for(int i=0; i<n; i++)
        {
            if(map.count(str1[i])==0) map[str1[i]] = 1;
            else map[str1[i]]++;
        }
        for(int i=0; i<n; i++)
        {
            if(map.count(str2[i])==0) return false;
            else if(--map[str2[i]]<0) return false;
        }
        return true;
    }

    bool process(string str1, string str2, int l1, int l2, int size)
    {
        //返回str1从l1开始向右size的子串与str2从l2开始向右size的子串是否为旋变词
        if(size==1) return str1[l1]==str2[l2];
        //在这里添加sameTypeSameNumber的判断
        if(!sameTypeSameNumber(str1.substr(l1,size), str2.substr(l2,size))) return false;
        for(int leftPart=1; leftPart<size; leftPart++)
        {
            if((process(str1, str2, l1, l2, leftPart) && process(str1, str2, l1+leftPart, l2+leftPart, size-leftPart))
            ||(process(str1, str2, l1,l2+size-leftPart, leftPart) && process(str1, str2, l1+leftPart, l2, size-leftPart)))
            return true;
        }
        return false;
    }
    bool isScramble(string str1, string str2)
    {
        if(!sameTypeSameNumber(str1, str2)) return false;
        int n = str1.size();
        return process(str1, str2, 0, 0, n);
    }

    bool isScrambleDp(string str1, string str2)
    {
        if(str1.empty() && str2.empty()) return true;
        if(str1.empty() || str2.empty()) return false;
        if(str1==str2) return true;
        if(!sameTypeSameNumber(str1, str2)) return false;

        //建立一个动态规划表，
        //dp[i][j][k]表示从str1的i位置出发长度为k的子串，
        //和从str2的j位置出发长度为k的子串
        //是否是旋变词
        //i的范围为[0, n-1], j的范围为[0, n-1], k的范围为[1, n], k=0的平面不用
        int n = str1.size();
        vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n,vector<bool>(n+1)));
        //先全部初始化为false
        for(int k=0; k<=n; k++) for(int i=0; i<n; i++) for(int j=0; j<n; j++) dp[i][j][k] = false;
        //当size=1时，dp的值取决于str1[i]和str2[j]是否相等
        for(int i=0; i<n; i++) for(int j=0; j<n; j++) dp[i][j][1] = (str1[i]==str2[j]);
        //对于其他普遍位置，根据递归求，外层循环是size从2到n，里面是i从0到n-size, j从0到n-size，然后是leftPart从1到size-1
        for(int k=2; k<=n; k++)
        {
            for(int i=0; i<=n-k; i++)
            {
                for(int j=0; j<=n-k; j++)
                {
                    for(int leftPart=1; leftPart<k; leftPart++)
                    {
                        if((dp[i][j][leftPart] && dp[i+leftPart][j+leftPart][k-leftPart])
                        ||(dp[i][j+k-leftPart][leftPart] && dp[i+leftPart][j][k-leftPart]))
                        {
                            dp[i][j][k] = true;
                            break;
                        }
                    }
                }
            }
        }
        return dp[0][0][n];
    }
};


int main()
{
    string str1, str2;
    cin >> str1;
    cin >> str2;
    Solution s;
    bool res = s.isScramble(str1, str2);
    bool res1 = s.isScrambleDp(str1, str2);
    cout << res << endl;
    cout << res1 << endl;
    return 0;
}
