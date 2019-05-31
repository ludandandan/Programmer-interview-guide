#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

class solution{
public:
    int aimMaxLength(vector<int> arr, int k)
    {
        if(arr.empty()) return 0;
        //key表示累加和，value表示位置
        map<int, int> m;
        int max_len = 0; //最终结果，每次有更长的就更新
        m.insert({0, -1});//在-1位置就可以做到累加和为0
        //这样是为了保证从0开始的累加和可以被计算进去
        int sum = 0; //实时记录当前的累加和
        for(int i=0; i<arr.size(); i++)
        {
            sum += arr[i]; //计算得到当前的sumi
            int gap = sum - k;
            //检查gap是否在map里面
            //若gap是0，那么0一定在map里面，因为我们一开始就把{0，-1}放进去了
            if(m.count(gap)==0)//若gap不在map里面，说明以i为结尾的子数组没有满足条件的
            {
                //检查这个sum是否有在map里，不在就添加记录，在就不用管了，因为需要出现最早的
                if(m.count(sum)==0)
                {
                    m.insert({sum, i});//不需要更新max_len，但是要向map中添加记录
                }
            }
            else
            {
                //若gap在里面，那么取出value，计算长度，更新max_len
                int len = i-(m[gap]+1)+1;
                max_len = max(max_len, len);
                //检查sum是否在map里，若不在添加
                if(m.count(sum)==0)
                {
                    m.insert({sum, i});
                }
            }
        }
        return max_len; 
    }

    int aimMaxLength2(vector<int> arr, int k)
    {
        if(arr.empty()) return 0;
        int max_len = 0;
        map<int, int> m;
        m.insert({0,-1});
        int sum = 0;
        for(int i=0; i<arr.size(); i++)
        {
            sum += arr[i];
            int gap = sum-k;
            if(m.count(gap)!=0)
            {
                int len = i-(m[gap]+1)+1;
                max_len = max(max_len, len);
            }
            if(m.count(sum)==0) m.insert({sum, i});
        }
        return max_len;
    }
};

int main()
{
    vector<int> arr{0,7,3,2,1,1,-6,-1,7,7};
    solution s;
    int res = s.aimMaxLength(arr, 7);
    cout << res << endl;
    int res2 = s.aimMaxLength2(arr, 7);
    cout << res2 << endl;
    return 0;

}
