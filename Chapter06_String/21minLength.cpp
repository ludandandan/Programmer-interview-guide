#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>
#define INT_MAX 65535
using namespace std;

class minLength{
public:
    int minLen(string str1, string str2)
    {
        //若str2的长度比str1大，那么就返回0表示子串不存在
        if(str2.size()>str1.size()) return 0;
        unordered_map<char, int> map; //key是字符，value是字符出现的次数
        //先对str2遍历，
        for(int i=0; i<str2.size(); i++)
        {
            if(map.count(str2[i])==0) map.insert({str2[i],1});
            else map[str2[i]]++;
        }
        int match = str2.size(); //共欠多少字符，
        //若key的value是正的就是欠的，若是负就是多还了的，还可以再收回来

        int right = 0;
        int left = 0;
        int res = INT_MAX;
        while(right<str1.size())
        {
            //先让right向右走直到不欠所有字符
            while(right<str1.size() && match!=0)
            {
                char c = str1[right];
                if(map.count(c)!=0)
                {
                    if(map[c]>0)
                    {
                        --match;
                    }
                    --map[c];
                }
                else
                {
                    map.insert({c, -1});
                }
                ++right;
            }
            //left回缩
            while(left<=right && match==0)
            {
                res = min(res, right-left);
                char c = str1[left];
                if(map[c]==0)
                {
                    ++match;
                }
                ++map[c];
                ++left;
            }
        }
        return res==INT_MAX?0:res;
    }
};

int main()
{
    string str1, str2;
    cin >> str1;
    cin >> str2;
    minLength m;
    int res = m.minLen(str1, str2);
    cout << res << endl;
    return 0;
}

