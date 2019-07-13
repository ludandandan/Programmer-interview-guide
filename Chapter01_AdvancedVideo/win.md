# 排成一条线的纸牌博弈问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/win.cpp)

**题目：**

给定一个整型数组arr，代表数值不同的纸牌排成一条线。玩家A和玩家B依次拿走每张纸牌，规定玩家A先拿，玩家B后拿，但是每个玩家每次只能拿走最左或最右的纸牌，玩家A和玩家B都绝顶聪明。请返回最后获胜者的分数。

**举例：**

arr = [1,2,100,4]

开始时，玩家A只能拿走1或者4。若是玩家A拿走1，则排列变为[2,100,4]，接下来玩家B可以拿走2或者4，然后继续轮到玩家A。若是开始时玩家A拿走4，则排列变为[1,2,100]，接下来玩家B可以拿走1或100，然后轮到玩家A拿。玩家A作为绝顶聪明的人不会先拿4，因为拿4之后，玩家B将会拿走100。所以玩家A先拿走1，让排列变为[2,100,4]，接下来不管玩家B怎么拿，100都会被玩家A拿走。玩家A会获胜，分数为101，返回101.

arr=[1,100,2]

开始时，玩家A不管是拿1还是2，玩家B作为绝顶聪明的人，都会把100拿走，玩家B会获胜，所以返回100.

**解析：**

方法一：暴力尝试

使用两个函数f(i, j)和s(i, j)。其中f(i, j) 表示在arr[i,...,j]上，让绝顶聪明的人先拿，那么最终这个人会得到什么分数，s(i, j)表示在arr[i,...,j]上，让绝顶聪明的人后拿，那么最终这个人会得到什么分数。

首先分析f(i, j):
   
    1. 若是i==j，那么就是还剩一张牌，让绝顶聪明的人先拿，她肯定就拿到这张牌了，所以返回arr[i]
   
    2. 若是i!=j，那么让决定聪明的人先拿，她有两种选择，一种是拿arr[i]，那么就剩下arr[i+1, j]，这下轮到这个人后拿，所以她拿arr[i]得到的分数就是(arr[i]+s(i+1,j))，同理，她拿arr[j]的分数就是(arr[j]+s(i,j-1))，作为绝顶聪明的人，她肯定是从这其中取得分最高的max(arr[i]+s(i+1,j), arr[j]+s(i,j-1))

然后分析s(i,j):
    1. 若是i==j，那么让绝顶聪明的人后拿，她肯定什么也拿不到，因为对方也是绝顶聪明的人，这种情况下的分数为0
    2. 若是i!=j，那么绝顶聪明的人后拿，先拿的人肯定会把最差的分数留给她，若是前面的人取走了arr[i]，那么留给她的就是f(i+1,j)，若是前面的人取走了arr[j]，那么留给她的就是f(i,j-1)，要从这里面找到最差的留给她，就是min(f(i+1, j), f(i, j-1))

分析时间复杂度：这个f(i,j)依赖s(i+1,j)和s(i,j-1)，然后s(i,j)又依赖f(i+1,j)和f(i, j-1)，时间复杂度为O(2^N)


方法二：动态规划
    两张二维dp表，分别为f表和s表。
    由于i<=j， 所以只需要填表的上半部分。对于f表，它的对角线为arr[i]，对于s表，她的对角线为0.
    然后就是一点一点填上去，填的顺序是，j从1到n， i从j-1到0，先填f后填s。最后需要max(dpf[0][n-1], dps[0][n-1])

```c++
class Solution{
public:
    int win(vector<int> arr)
    {
        if(arr.empty() || arr.size()==0) return 0;
        return max(f(arr, 0, arr.size()-1), s(arr, 0, arr.size()-1));
    }

    //让绝顶聪明的人先拿，那么他会得到多少分
    int f(vector<int> &arr, int i, int j)
    {
        if(i==j) return arr[i];
        return max(arr[i]+s(arr, i+1, j), s(arr, i, j-1)+arr[j]);
    }

    //让绝顶聪明的人后拿，那么他会得到多少分
    int s(vector<int> &arr, int i, int j)
    {
        if(i==j) return 0;
        return min(f(arr, i+1, j), f(arr, i, j-1));
    }

    int winDp(vector<int> arr)
    {
        if(arr.empty() || arr.size()==0) return 0;
        int n = arr.size();
        //建两张dp表，一个f，一个s
        vector<vector<int>> dpf(n, vector<int>(n));
        vector<vector<int>> dps(n, vector<int>(n));
        for(int i=0; i<n; i++) 
        {
            dpf[i][i] = arr[i];
            dps[i][i] = 0;
        }
        for(int j=1; j<n; j++)
        {
            for(int i=j-1; i>=0; i--)
            {
                dpf[i][j] = max(arr[i]+dps[i+1][j], arr[j]+dps[i][j-1]);
                dps[i][j] = min(dpf[i+1][j], dpf[i][j-1]);
            }
        }
        return max(dpf[0][n-1], dps[0][n-1]);
    }
};


```