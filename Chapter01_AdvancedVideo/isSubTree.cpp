#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

class Solution
{
public:
    bool isSubTree(TreeNode *t1, TreeNode *t2)
    {
        //查找t2是否在t1里
        string str = serialByPre(t1);
        string match = serialByPre(t2);
        /*
        //直接使用string的find方法
        if(str.find(match)!=string::npos) return true;
        else return false;
        */

        //自己实现KMP方法
        if(strStr(str, match)!=-1) return true;
        else return false;
    }
    //将树按照先序序列化
    string serialByPre(TreeNode *root)
    {
        if(root==nullptr) return "#_";
        string res = to_string(root->val) + "_";
        res += serialByPre(root->left);
        res += serialByPre(root->right);
        return res;
    }

    //KMP方法
    //返回match在str中的位置，若match在str中不存在就返回-1
    int strStr(string str, string match)
    {
        int sn = str.size();
        int mn = match.size();
        if(str.empty() || mn>sn) return -1;
        //为match生成next数组
        vector<int> next = getNext(match);
        int si = 0;
        int mi = 0;
        //只要有一个字符串到最后了就停止循环
        while(si<sn && mi<mn)
        {
            if(str[si]==match[mi])
            {
                si++;
                mi++;
            }
            else
            {
                //若是不匹配了，mi往前跳
                if(next[mi]==-1)
                {
                    //若跳到头了,说明str[si]连match[0]都匹配不出来
                    si++;
                }
                else
                {
                    //若是还可以往前跳
                    mi = next[mi];
                }
            }
        }
        return mi==mn?si-mi:-1;
    }

    //得到next数组
    vector<int> getNext(string str)
    {
        int n = str.size();//n至少是1
        vector<int> next(n);
        if(n==1)
        {
            next[0] = -1;
            return next;
        }
        next[0] = -1;
        next[1] = 0;
        int i = 2;
        int cn = 0;//cn表示跳到的位置, 最长前缀的后一个
        while(i<n)
        {
            if(str[i-1]==str[cn])
            {
                next[i++] = (++cn);
            }
            else if(cn>0)
            {
                cn = next[cn];
            }
            else
            {
                next[i++] = 0;
            }
        }
        return next;
    }
    
};


int main()
{
    TreeNode A1(1);
    TreeNode A2(2);
    TreeNode A3(3);
    TreeNode A4(4);
    TreeNode A5(5);
    TreeNode A6(6);
    TreeNode A7(7);
    TreeNode A8(8);
    TreeNode A9(9);

    TreeNode B2(2);
    TreeNode B4(4);
    TreeNode B5(5);
    TreeNode B8(8);
    TreeNode B9(9);

    A1.left = &A2;
    A1.right = &A3;
    A2.left = &A4;
    A2.right = &A5;
    A3.left = &A6;
    A3.right = &A7;
    A4.right = &A8;
    A5.left = &A9;

    B2.left = &B4;
    B2.right = &B5;
    B4.right = &B8;
    B5.left = &B9;

    Solution s;
    bool res = s.isSubTree(&A1, &B2);
    cout << res << endl;
/*
    string str, match;
    cin >> str;
    cin >> match;
    int res2 = s.strStr(str, match);
    cout << res2 << endl;
*/

    return 0;
}
