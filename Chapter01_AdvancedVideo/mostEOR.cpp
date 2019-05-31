#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class solution{
public:
    int mostEOR(vector<int> arr)
    {
        if(arr.empty()) return 0;
        int sum = 0;//0异或任何数仍然是那个数
        map<int, int> m; //key表示异或和，value表示这个异或和出现的最晚的位置
        m.insert({0, -1});//先放进去一个打底的
        vector<int> dp(arr.size());
        dp[0] = 1;//只有一个数时只能划分为1个

        for(int i=1; i<arr.size(); i++)
        {
            sum = sum^arr[i];//当前的异或和
            dp[i] = dp[i-1];//这是一种情况
            if(m.count(sum)!=0)//若最后一部分可以异或和0
            {
                int k = m[sum];//k还有可能是-1，
                //这时候就说明sum=0,并且前面除了-1之外没有一个可以使异或和为0了，
                //也就是说最优划分是把0到i划分为一块，除此之外没有异或和为0的分割方式了
                int tmp = k==-1?1:(dp[k]+1);
                dp[i] = max(dp[i], tmp);
                //更新map
                m[sum] = i;
            }
            else
            {
                //更新sum
                m.insert({sum, i});
            }
        }
        return dp[arr.size()-1];
    }
};

int main()
{
    solution s;
    vector<int> arr{3,2,1,9,0,7,0,2,1,3};
    int res = s.mostEOR(arr);
    cout << res << endl;
    return 0;
}
