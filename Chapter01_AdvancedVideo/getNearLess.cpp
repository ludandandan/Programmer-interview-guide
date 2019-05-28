#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;

class getNearLess{
public:
    vector<vector<int>> getNearLess1(vector<int> arr)
    {
        //暴力方法，分别向左向右扩，找到比cur大的就记录它的位置
        //若越界了也没有就记录为0
        int n = arr.size();
        vector<vector<int>> res(n,vector<int>(2));
        for(int i=0; i<n; i++) for(int j=0; j<2; j++) res[i][j] = -1;
        for(int i=0; i<n; i++)
        {
            for(int j=i-1; j>=0; j--)
            {
                if(arr[j]<arr[i]) 
                {
                    res[i][0] = j;
                    break;
                }
            }
            for(int j=i+1; j<n; j++)
            {
                if(arr[j]<arr[i])
                {
                    res[i][1] = j;
                    break;
                }
            }
        }
        return res;
    }

    vector<vector<int>> getNearLess2(vector<int> arr)
    {
        //使用单调栈，从栈底到栈顶从小到大,栈里面放位置，
        //因为无重复元素，所以栈里面只需要放整型
        stack<int> s;
        int n = arr.size();
        vector<vector<int>> res(n,vector<int>(2));
        for(int i=0; i<n; i++)
        {
            while(!s.empty() && arr[s.top()]>arr[i])
            {
                //往外弹的时候生成信息
                int index = s.top();
                s.pop();
                //谁让她弹出来，这个数就是右边比它小的
                res[index][1] = i;
                //它下面的就是左边比离它最近的比它小的
                res[index][0] = s.empty()?-1:s.top();
            }
            s.push(i);
        }
        while(!s.empty())
        {
            int index = s.top();
            s.pop();
            //不因为谁而弹出来，那么它右边比它大的是-1
            res[index][1] = -1;
            res[index][0] = s.empty()?-1:s.top();
        }
        return res;
    }


    //对于有重复数字的，栈里面可能会压同时压入多个位置信息，
    //此时栈中应该放vector
    vector<vector<int>> getNearLess3(vector<int> arr)
    {
        stack<vector<int>> s;
        int n = arr.size();
        vector<vector<int>> res(n, vector<int>(2));

        for(int i=0; i<n; i++)
        {
            //栈从底到顶从小到大
            while(!s.empty() && arr[s.top()[0]]>arr[i])
            {
                //i让它弹出来的，那么它右边比它小的就是i
                vector<int> indexs = s.top();
                s.pop();
                for(int j: indexs)
                {
                    res[j][1] = i;
                //它下面的是左边比它小的
                    res[j][0] = s.empty()?-1:s.top()[s.top().size()-1];//取最晚加入的那个
                }
            }
            //若是相等，那么就一起压入栈中
            if(!s.empty() && arr[s.top()[0]]==arr[i])
            {
                s.top().push_back(i);
            }
            else //否则就自己一个vector压入栈
            {
                vector<int> tmp;
                tmp.push_back(i);
                s.push(tmp);
            }
        }
        //若是处理完了还有一些在栈里面
        while(!s.empty())
        {
            vector<int> indexs = s.top();
            s.pop();
            //这些右边比他们大的是-1
            for(int j: indexs)
            {
                res[j][1] = -1;
                res[j][0] = s.empty()?-1:s.top()[s.top().size()-1];
            }
        }
        return res;
    }
};

int main()
{
    getNearLess g;
    vector<int> arr{2,3,4,1,2,5,3,6,2,7};
    vector<vector<int>> res1 = g.getNearLess1(arr);
    for(auto r: res1)
    {
        for(int m: r)
        {
            cout << m << ",";
        }
        cout << endl;
    }
    cout << endl;
    vector<vector<int>> res3 = g.getNearLess3(arr);
    for(auto r: res3)
    {
        for(int m: r)
        {
            cout << m << ",";
        }
        cout << endl;
    }
    return 0;
}
