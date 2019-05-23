#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <deque>
using namespace std;

class getWindowsMaxArr{
public:
    vector<int> getArr(vector<int> arr, int w)
    {
        vector<int> res;
        if(arr.empty() || arr.size()<w) return res;

        deque<int> deq; //存窗口内最大值的索引
        int r=0; //窗口的右边界
        
        while(r<arr.size())
        {
            //窗口内进数,从头到尾是从大到小
            while(!deq.empty() && arr[deq.back()]<=arr[r])
            {
                deq.pop_back();//要是deq里的小就弹出来，弹弹弹，弹到死
            }
            //弹好了以后从尾巴进去
            deq.push_back(r);
            //检查deq的头部有无过期
            if(deq.front() == r-w) deq.pop_front();
            if(r>=w-1) res.push_back(arr[deq.front()]);
            r++;
        }
        return res;
    }
};


int main()
{
    vector<int> arr{4,3,5,4,3,3,6,7};
    getWindowsMaxArr m;
    vector<int> res = m.getArr(arr,3);
    for(int r: res)
    {
        cout << r << ",";
    }
    cout << endl;
    return 0;
}
