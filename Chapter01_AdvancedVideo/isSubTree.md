# 判断t1树中是否有与t2树拓扑结构完全相同的子树（子树包含问题）
[完整代码]()

**题目：**

给定彼此独立的两棵树头节点分别为t1和t2，判断t1中是否有与t2树拓扑结构完全相同的子树。

**举例：**

详细例子参照<程序员面试指南>Page144

**解析：**

先把t1和t2按照相同的规则序列化为str和match，然后应用KMP算法查找str中是否有match，其实string的find方法就可以实现字符串中子串的查找。
```c++
size_t pos = str.find(match);//返回match在str中第一次出现的位置，若在str中不存在match，那么就返回string::npos
```

```c++
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
```