#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#define INT_MIN -65535
using namespace std;


//建一个字典树，32层，每层有01两条路
//这个字典树不需要path和end变量，因为固定为32层，
//并且不在意每个节点经过的多少
class trieNode{
public:
    int path;
    trieNode *next[2];
    trieNode():path(0){}
};

class trieTree{
public:
    trieNode *root = new trieNode();
    void add(int n)
    {
        //把一个32位整型放进字典树
        trieNode *cur = root;
        for(int i=31; i>=0; i--)
        {
            int path = ((n>>i)&1);
            cur->next[path] = cur->next[path]==nullptr?new trieNode():cur->next[path];
            cur = cur->next[path];
        }
    }

    //给定一个eorj表示以j结尾的情况下的arr[0,...,j]的异或和
    //因为eor[0],eor[1],...,eor[j-1]已经添加到字典树里面了，
    //那么从这里面找到一个eor[x]使它于eorj异或之后异或和最大的一个,返回这个异或和
    int maxXor(int eorj)
    {
        //符号位希望相同，其他位希望相反
        trieNode *cur = root;
        int res = 0;
        //先高位，再低位
        for(int i=31; i>=0; i--)
        {
            //先看看自己是多少
            int path = ((eorj>>i)&1);
            //再看看最好能得到多少
            int best = i==31?path:(path^1);
            //再看看可以得到的最好是多少
            best = cur->next[best]==nullptr?(best^1):best;
            res |= ((path^best)<<i);
            cur = cur->next[best];
        }
        return res;
    }
};


//求子数组的最大异或和
class maxEOR{
public:
    //暴力
    int maxEOR1(vector<int> arr)
    {
        if(arr.empty()) return 0;
        int res = INT_MIN;
        int n = arr.size();
        //记录从0到i的异或和
        vector<int> eor(n, 0);
        //先遍历一遍把所有异或和计算出来
        eor[0] = arr[0];
        for(int i=1; i<n; i++)
        {
            eor[i] = arr[i]^eor[i-1];
        }

        //对每一个子数组计算
        //必须以end结尾的子数组的最大异或和
        for(int end=0; end<n; end++)
        {
            for(int start=0; start<=end; start++)
            {
                //[start, end]子数组的异或和
                int eori = start==0?eor[end]:eor[end]^eor[start-1];
                res = max(res, eori);
            }
        }
        return res;
    }

    int maxEOR2(vector<int> arr)
    {
        if(arr.empty()) return 0;
        trieTree t;
        t.add(0);//先把0放进去打通32层
        
        int res = INT_MIN;
        int eor = 0;
        //必须以i结尾的子数组的最大异或和
        for(int i=0; i<arr.size(); i++)
        {
            eor ^= arr[i];
            res = max(t.maxXor(eor), res);
            t.add(eor);
        }
        return res;
    }
};

int main()
{
    maxEOR m;
    vector<int> arr{3, -28, -29, 2, 11, 1, 15, 10, 13, 4};
    int res1 = m.maxEOR1(arr);
    cout << res1 << endl;
    int res2 = m.maxEOR2(arr);
    cout << res2 << endl;
    return 0;
}
