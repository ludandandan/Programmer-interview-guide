#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
#define INT_MAX 65535
using namespace std;
 
int main()
{
    int N, K;
    cin >> N >> K;
    vector<int> count(10, 0); //统计每个数字已经出现的次数
    string s;
    cin >> s;
    for (int i = 0; i < N; i++)
    {
        int tmp = s[i] - '0';
        count[tmp]++;
    }
 
    //遍历0-9的每个数字，计算以每个数字出现k次的最小花费，其中最小的那个就是所要的
    //定义全局的最小花费及其对应的数字串
    int g_minCost = INT_MAX;
    string res;
    for (int i = 0; i < 10; i++)
    {
        string tmp = s; //在tmp上做替换操作不会影响到s
        int need = K - count[i]; //需要转换多少个数字
        int gap = 1; //其他数字转换为当前数字i的代价，从最小的代价开始，直到need==0
        int cost = 0;
        //寻找数字i出现K次的最小花费
        while (need != 0)
        {
            //代价为gap可转为i的数字有gap+i和gap-i，但要保证其在0-9范围内
            if (gap + i <= 9)
            {
                char c = gap + i + '0';
                if (count[gap+i]>0 && count[gap + i] <= need)
                {
                    cost += gap * count[gap + i];
                    need -= count[gap + i];
                    for (int j = 0; j < N; j++)
                    {
                        if (tmp[j] == c) tmp[j] = char(i + '0');
                    }
                }
                else if(count[gap+i]>need) //若是大于need,由大变小，从前往后
                {
                    int j = 0;
                    cost += need * gap;
                    while (need != 0)
                    {
                        if (tmp[j] == c)
                        {
                            tmp[j] = char(i + '0');
                            need--;
                        }
                        j++;
                    }
                }
            }
 
            if (i - gap >= 0)
            {
                char c = i - gap + '0';
                if (count[i-gap]>0 && count[i - gap] <= need)
                {
                    need -= count[i - gap];
                    cost += gap * count[i - gap];
                    for (int j = 0; j < N; j++)
                    {
                        if (tmp[j] == c) tmp[j] = char(i + '0');
                    }
                }
                else if(count[i-gap]>need)//若是比需要的多，从小变大，为了字典序最小应从后往前变
                {
                    cost += gap * need;
                    int j = N - 1;
                    while (need != 0)
                    {
                        if (tmp[j] == c)
                        {
                            tmp[j] = char(i + '0');
                            need--;
                        }
                        j--;
                    }
                }
            }
            gap++; //若是gap+i 和 i-gap两个数的变换仍不满足要求就扩大gap继续计算
        }
        //计算好的cost和tmp字符串，通过与g_minCost对比看要不要更新res
        if (cost < g_minCost)
        {
            res = tmp;
            g_minCost = cost;
        }
    }
    cout << g_minCost << endl;
    cout << res << endl;
    return 0;
}