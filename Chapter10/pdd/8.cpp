#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
 
int maxIdx(vector<int> arr);
bool dfs(vector<int> &arr, vector<int> &res, int n, int &m, int step);
 
int main()
{
    int n;
    int m = 0;
    cin >> n;
    //arr[i]表示(i+1)品种的树有arr[i]棵
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        m += arr[i];
    }
    vector<int> res(m);
    int step = 0;
 
    if (dfs(arr, res, n, m, step))
    {
        for (int num : res)
        {
            cout << num << ' ';
        }
        cout << endl;
    }
    else cout << "-" << endl;
    getchar();
    return 0;
 
}
 
//计算当前arr中棵树最多的树的品种索引
int maxIdx(vector<int> arr)
{
    int max_count = 0;
    int idx = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > max_count)
        {
            idx = i + 1;
            max_count = arr[i];
        }
        return idx;
    }
}
 
bool dfs(vector<int> &arr, vector<int> &res, int n, int &m, int step)
{
    //arr为树的品种与棵数关系， res为当前的结果， n为树的品种数， m为树的总数， step为在res中处理到第几个坑了
    int idx = maxIdx(arr); //当前棵数最多的树的品种
    if (m == 0) return true; //表示树已经种完了
    //剪枝
    if (arr[idx] > (m + 1) / 2) return false;
    else
    {
        //为了使得字典序最小，从小到大的遍历每个品种，有小品种可以用就先用小的
        for (int i = 0; i < n; i++)
        {
            //若是当前品种的树棵数大于0，并且当前位置step的前一个坑里放的不是当前品种或者这是第一个坑，前面没有树
            //那么就可以在step坑里放arr[i]这个品种的树，同时arr[i]的棵数减1， 总的数目的棵数减少1
            if (arr[i] > 0 && (step == 0 || res[step - 1] != (i + 1)))
            {
                arr[i]--;
                m--;
                res[step] = i + 1;
                //然后处理下一个坑，深度优先遍历
                if (dfs(arr, res, n, m, step + 1)) return true;
                //否则就是在这个坑里放这个品种的树不行，再拔出来
                arr[i]++;
                m++;
            }
        }
    }
    return false;
}
