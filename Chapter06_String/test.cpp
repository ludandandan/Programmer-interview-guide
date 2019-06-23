#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <sstream>
#define LOCAL
using namespace std;


int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int t;
    cin >> t;//t组数据
    for(int i=0; i<t; i++)
    {
        int n,k;
        cin >> n >> k;
        //有2n个数，洗牌k次
        //把2n个数读进来
        vector<int> pre(2*n);
        for(int m=0; m<2*n; m++)
        {
            cin >> pre[m];
        }
        //[0, n-1]一波，[n,2n-1]一波
        vector<int> res(2*n);//用于进行洗牌
        for(int m=0; m<2*n; m++)
        {
            int tmp = m+1; //下标从1开始
            for(int j=0; j<k; j++)
            {
                tmp = tmp<=n? 2*tmp-1:(tmp-n)*2;
            }
            res[tmp-1] = pre[m];
        }
        //k次洗好之后放在pre中，然后我们把它放在oss里面
        for(int m=0; m<2*n-1; m++)
        {
            cout << pre[m] << " ";
        }
        cout << pre[2*n-1] << endl;
    }
}

