# 单调栈结构
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/getNearLess.cpp)

**题目：**

给定一个不含有重复值的数组arr，找到每一个i位置左边和右边离i位置最近且值比arr[i]小的位置。返回所有位置相应的信息。

**举例：**

arr=[3,4,1,5,6,2,7]
返回如下二维数组：
    {{-1,2},{0,2},{-1,-1},{2,5},{3,5},{2,-1},{5,-1}}

-1表示不存在。

**进阶问题：**
给定一个可能寒重复值的数组arr，找到每一个i位置左边和右边离i位置最近且值比arr[i]小的位置。返回索引位置相应的信息。

**解析：**
### **原问题：**
方法一：使用暴力方法实现。使用暴力方法也可以实现进阶问题。

从cur开始分别向右向左遍历找到离它最近的比它小的和左边离他最近的比它小的，并记录下位置，若是越界了都没有找到，那么就记录为-1.


方法二：
使用单调栈实现。

因为题目是要求离它最近的比它小的，所以就建一个栈，从底到顶是从小到大的。又原问题中不含有重复数字，所以这里栈里面只需要放整型变量表示位置。0位置进栈后发现1位置的4比0位置的3大，直接进栈，然后又发现2位置的1比当前栈顶1位置的4小，那么1就要出栈。

若有元素要出栈，那么这个元素的相应的信息就要生成了。
1. 谁让它出栈的那么这个数就是它右边离它最近的比它小的。
2. 它底下的元素是谁，那么这个数就是它左边离它最近的比它小的。

若是整个数组都遍历完一遍了，栈里面还有元素，那么对于这些元素，他们并不是因为谁比它小而弹出来的，那么
1. 右边离它最近的比它小的没有数，记为-1
2. 左边离它最近的比它小的还是它下面的元素

若是栈到底了，下面没有元素了，那么左边离它最近的比它小的就没有，记录为-1.

### **进阶问题：**
与原问题相比，进阶问题中可能会出现重复元素。遇到重复元素就把相同的元素同时压到栈里面去，到时弹出时一起结算。所以栈中的元素应该是vector<int>类型的。


**时间复杂度：**
每个元素只进栈一次，出栈一次，所以时间复杂度为O(N)

```c++
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
```
