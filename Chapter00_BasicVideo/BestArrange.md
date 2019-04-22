## 会议室宣讲
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/BestArrange.cpp)

**题目：**
> 一些项目要占用一个会议室宣讲，会议室不能同时容纳两个项目的宣讲。给你每个项目开始的时间和结束的时间（给你一个数组，里面是一个一个的项目）。你来安排宣讲的日程，要求会议室进行的宣讲场次最到。返回这个最多的宣讲场次。

> 贪心策略：哪个早结束哪个先进行，然后淘汰掉因为这个项目宣讲而不能宣讲的项目（即淘汰掉开始时间在这个项目结束时间之前的项目）。
> 首先需要定义一个数据结构program，这结构中包括start和end两个数据成员分别表示该项目开始时间和结束时间。同时需要一个cur表示当前时间。将所有项目放到一个vector<program*>中，并按照结束时间早的排在前面进行排序（所以还需要定义一个比较器）。按照结束时间早的往后找，找到一个项目它的开始时间在当前时间cur之后，那么就安排它宣讲，同时将当前时间推迟到这个项目的结束时间。并且用于记录总的宣讲场次的变量加1。最后返回总的宣讲场次。

```c++
struct program{
    int start;
    int end;
    program(int s, int e): start(s), end(e){}
};

bool endEarly(program *p1, program *p2)
{
    return (p1->end) < (p2->end);
}
int bestArrange(vector<int> start, vector<int> end)
{
    int n = start.size();
    vector<program*> vp;
    for(int i=0; i<n; i++)
    {
        program *p = new program(start[i], end[i]);
        vp.push_back(p);
    }
    return bestArrange(vp, 0);
}

// cur表示当前时刻
int bestArrange(vector<program*> vp, int cur)
{
    sort(vp.begin(), vp.end(), endEarly);
    int n = vp.size();
    int res = 0;
    for(int i=0; i<n; i++)
    {
        if(cur<=vp[i]->start)
        {
            res++;
            cur = vp[i]->end;
        }
    }
    return res;
}

```