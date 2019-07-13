# 子数组的最大异或和
[完整代码]()

**题目：**

数组的异或和的定义是把数组中所有的数异或起来得到的值。
给定一个整型数组arr，其中可能有正，有负，有零，求其中子数组的最大异或和。

**举例：**

arr={3}，数组中只有一个元素，所以只有一个子数组，就是这个数组本身，最大异或和为3.

arr={3,-28,-29,2}，子数组有很多，但是{-28, -29}这个子数组的异或和为7，是所有子数组中最大的。

**要求：**
如果arr长度为N，时间复杂度O(N)

**解析：**

方法一： 暴力
    可以尝试找到以每个元素结尾的子数组中最大的异或和，再从中找到最大的就是全部子数组中最大的了。以arr[i]结尾的子数组有arr[i,i], arr[i-1, i], arr[i-2, i-1, i],..., arr[0, ..., i]。可以先计算0到i的异或和，那么arr[j, ..., i]的异或和就是0到i的异或和再异或上0到(j-1)的异或和。这样的时间复杂度就是枚举所有子数组的时间复杂度O(N^2).


方法二：字典树
    在寻找以i位置结尾的子数组中谁的异或和最大时，可以使用字典树一下子就找到。因为我们已经有0到i的异或和了，我们希望异或后的数越大越好，符号位希望异或为0，即符号位相同。其他位，从高到低，相反最好。先满足高位相反。即对于每一位，我们都有一个希望的数，然后在字典树里寻找，有没有这个数。字典树里存储的是从0到后面任意位置的异或和。因为Int为32位，所有有32层，每一层都有两条路径（0和1）.

    定义一个字典树的节点类，它有两条路径。然后定义一个字典树的类，需要一个可以往里面添加元素的方法和一个根据给定的数字num（0到i的异或和），给出（以i结尾的）最大异或和的方法。

```c++

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
```