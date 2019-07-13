#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#define INT_MIN -65535
using namespace std;

struct Node{
    Node *next[2];//两条路径0和1
    Node():next{nullptr}{}
};


class TrieTree{
public:
    Node root;
    //添加数字
    void add(int num)
    {
        //一位一位的添加，先添加高位，再添加低位
        Node *cur = &root;
        for(int i=31; i>=0; i--)
        {
            int path = ((num>>i)&1); //当前位是0还是1
            if(cur->next[path]==nullptr)
            {
                cur->next[path] = new Node();
            }
            cur = cur->next[path];
        }
    }

    //根据给定的数字，给出以i结尾的数字的最大异或和
    int getMaxXor(int num)
    {
        //根据数字，得到最好的路径，最想要的路径
        Node *cur = &root;
        int res = 0;
        for(int i=31; i>=0; i--)
        {
            int path = ((num>>i)&1);
            int bestPath = i==31?path:path^1;
            bestPath = cur->next[bestPath]==nullptr?bestPath^1:bestPath;
            res |= (path^bestPath)<<i;
            cur = cur->next[bestPath];
        }
        return res;
    }
};


class Solution{
public:
    //暴力方法
    int maxXor(vector<int> arr)
    {
        if(arr.empty() || arr.size()==0) return 0;
        //创建一个数组eor，保存0到i的异或和
        int n = arr.size();
        vector<int>eor(n);
        eor[0] = arr[0];
        int maxRes = INT_MIN;
        for(int i=1; i<n; i++)
        {
            eor[i] = eor[i-1]^arr[i];
        }
        for(int end=0; end<n; end++)
        {
            for(int start=end; start>=0; start--)
            {
                if(start==0) maxRes = max(maxRes, eor[end]);
                else maxRes = max(maxRes, eor[end]^eor[start-1]);
            }
        }
        return maxRes;
    }


    //字典树的方法
    int maxXorByTrieTree(vector<int> arr)
    {
        TrieTree tree;
        tree.add(0);//先打通所有的层
        //以每个位置为结尾的异或和的最大值
        int res = INT_MIN;
        int eor = 0;
        for(int i=0; i<arr.size(); i++)
        {
            eor ^= arr[i];
            res = max(res, tree.getMaxXor(eor));
            tree.add(eor);
        }
        return res;
    }
};




int main()
{
    Solution s;
    vector<int> arr{3, -28, -29, 2};
    int res = s.maxXor(arr);
    cout << res << endl;
    //Node node;
    //if(node.next[0]==nullptr) cout << "hahaha" << endl;
    //if(node.next[1]==nullptr) cout << "gagaga" << endl;
    int res2 = s.maxXorByTrieTree(arr);
    cout << res2 << endl;
    return 0;
}
