# 未排序数组中累加和为给定值的最长子数组系列问题
[完整代码]()

**题目：**
给定一个无序数组arr，其中元素可正，可负，可0，给定一个整数k，求arr所有的子数组中累加和为k的最长子数组长度。

补充问题1:
  
    给定一个无序数组arr，其中元素可正，可负，可0， 求arr所以子数组中正数与负数个数相等的最长子数组长度。

补充问题2:
    
    给定一个无序数组arr，其中元素只是0和1，求arr所有子数组中0和1个数相等的最长子数组长度

补充问题3:
    
    给定一个无序数组arr，其中元素只是0，1和2，求arr所有子数组中1和2个数相等的最长子数组长度。

补充问题4:
    
    给定一个无序数组arr，其中元素只是1，2和3，求arr所有子数组中1和2个数相等的最长子数组长度。

**解答：**

遇到求子数组，子串这种连续的一段，一种普遍思路是：若是必须以某个位置i结尾的情况下可以求出某个答案，那么最终答案一定在其中。

那么这个题目我们可以求必须以i位置结尾的情况下累加和为k的最长子数组，然后再从这里面选出最长的。

必须以i位置结尾的子数组有[0,i],[1,i],[2,i],..., [i-1,i]和[i,i]，那么再这里面找到累加和为k的，若是有多个累加和为k的，那么就选最长的。可以遍历找到累加和为K的，但是这样时间复杂度就变成了O(N^3). 若sumi表示从0累加到i的和，那么我们只需要找到一个位置j，从0到j的和为sumi-k,那么[j+1, i]的累加和就是k，只需要找离i最远的j即可。我们可以用一个map记录出现过的累加和sum和这个累加和sum最早出现在什么位置。即map的key表示累加和sum，value表示这个累加和出现的位置i。累加和sum是指从0加到位置i的和。若计算必须以i位置结尾的子数组累加和为k的最长子数组，那么可以先得到sumi(sumi可以由sum(i-1)加上arr[i]得到),然后计算sumi-k，看看这个数在map里面是否存在（因为是从左到右计算的，i位置前面的累加和都记录在里面了），若存在，那么取出value = map[sumi-k]，那么[value+1, i]就是必须以i位置结尾的累加和为k的最长子数组（因为Key的value是记录key累加和最早出现的位置，那么也就是离i最远的，最长的）。若是不存在，那么必须以i位置结尾的子数组中没有累加和为k的。

这样把arr遍历一遍，边遍历边计算sumi，记录在map里面，同时统计max_len，遍历完一遍结果也就得到了，所以时间复杂度为O(N)。因为需要map进行记录所以空间复杂度O(N)

**对补充问题的解答：**

补充问题1: 将奇数转换为1， 偶数转换为-1，计算最长累加和为0的最长子数组

补充问题2: 将0转换为-1，计算最长累加和为0的最长子数组

补充问题3：将2转换为-1， 计算最长累加和为0的最长子数组

补充问题4: 将3转换为0， 2转换为-1，计算最长累加和为0的最长子数组


```c++
class solution{
public:
    int aimMaxLength(vector<int> arr, int k)
    {
        if(arr.empty()) return 0;
        //key表示累加和，value表示位置
        map<int, int> m;
        int max_len = 0; //最终结果，每次有更长的就更新
        m.insert({0, -1});//在-1位置就可以做到累加和为0
        //这样是为了保证从0开始的累加和可以被计算进去
        int sum = 0; //实时记录当前的累加和
        for(int i=0; i<arr.size(); i++)
        {
            sum += arr[i]; //计算得到当前的sumi
            int gap = sum - k;
            //检查gap是否在map里面
            //若gap是0，那么0一定在map里面，因为我们一开始就把{0，-1}放进去了
            if(m.count(gap)==0)//若gap不在map里面，说明以i为结尾的子数组没有满足条件的
            {
                //检查这个sum是否有在map里，不在就添加记录，在就不用管了，因为需要出现最早的
                if(m.count(sum)==0)
                {
                    m.insert({sum, i});//不需要更新max_len，但是要向map中添加记录
                }
            }
            else
            {
                //若gap在里面，那么取出value，计算长度，更新max_len
                int len = i-(m[gap]+1)+1;
                max_len = max(max_len, len);
                //检查sum是否在map里，若不在添加
                if(m.count(sum)==0)
                {
                    m.insert({sum, i});
                }
            }
        }
        return max_len; 
    }

    int aimMaxLength2(vector<int> arr, int k)
    {
        if(arr.empty()) return 0;
        int max_len = 0;
        map<int, int> m;
        m.insert({0,-1});
        int sum = 0;
        for(int i=0; i<arr.size(); i++)
        {
            sum += arr[i];
            int gap = sum-k;
            if(m.count(gap)!=0)
            {
                int len = i-(m[gap]+1)+1;
                max_len = max(max_len, len);
            }
            if(m.count(sum)==0) m.insert({sum, i});
        }
        return max_len;
    }
};
```