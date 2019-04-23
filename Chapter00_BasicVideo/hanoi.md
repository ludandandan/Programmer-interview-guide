## 汉诺塔问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/hanoi.cpp)

**题目：**
> 给定一个整数n，代表汉诺塔游戏中从小到大放置的n个圆盘，假设开始时所有的圆盘都放在左边的柱子上，想按照汉诺塔游戏的要求（每次只能挪动一个圆盘，只能小压大不能大压小）把所有的圆盘都移动到右边的柱子上。实现函数打印最优移动轨迹。

> 不在考虑左中右，而是考虑from，to，help三个柱子，将from上的圆盘移动到to上，借助help的帮助。
> 
> 汉诺塔问题可以分为三步：
> 
> 假设现在是移动从1\~N的圆盘的过程，圆盘原来都是在from柱子上，想要移动到to柱子上，需要借助help柱子的帮助。
> 1. 将1\~n-1从from移动到help上。
> 2. 将第n个圆盘从from移动到to上。
> 3. 将1\~n-1从help移动到to上。
> 4. base case: 当n==1时，这时直接将这个圆盘从from移动到to上。

> 汉诺塔问题的时间复杂度分析：T(n) = T(n-1) + O(1) + T(n-1) = 2T(n-1)+ O(1)
> 可知这时一个等比数列求和问题，结论是对于n层汉诺塔问题，最少需要$2^{n}-1$步才可完成。故时间复杂度为$O(2^{n})$。
```c++
void hanoi(int n)
{
    process(n, "left", "right", "middle");
}

void process(int n, string from , string to, string help)
{
    if(n==1) cout << "move 1 from " << from << " to " << to << endl;
    else
    {
        process(n-1, from, help, to);
        cout << "move " << n << " from " << from << " to " << to << endl;
        process(n-1, help, to, from);
    }
}
```    

> 若没有考虑到使用通用的from,to,help来表示三个柱子，那么可以使用6个函数(fromLeftToRight, fromLeftToMid, fromMidToLeft, fromMidToRight, fromRightToMid, fromRightToLeft)相互嵌套来实现。

```c++
void FromLeftToRight(int n)
{
    if(n==1) 
    {
        cout << "move 1 from left to right" << endl;
        return;
    }
    FromLeftToMid(n-1);
    cout << "move " << n << " from left to right"  << endl;
    FromMidToRight(n-1);
}

void FromLeftToMid(int n)
{
    if(n==1)
    {
        cout << "move 1 from left to middle" << endl;
        return;
    }
    FromLeftToRight(n-1);
    cout << "move " << n << " from left to middle" << endl;
    FromRightToMid(n-1);
}

void FromRightToMid(int n)
{
    if(n==1)
    {
        cout << "move 1 from right to middle" << endl;
        return;
     }
    FromRightToLeft(n-1);
    cout << "move " << n << " from right to middle" << endl;
    FromLeftToMid(n-1);
}

void FromRightToLeft(int n)
{
    if(n==1)
    {
        cout << "move 1 from right to left" << endl;
        return;
    }
    FromRightToMid(n-1);
    cout << "move " << n << " from right to left" << endl;
    FromMidToLeft(n-1);
}

void FromMidToRight(int n)
{
    if(n==1)
    {
        cout << "move 1 from middle to right" << endl;
        return;
    }
    FromMidToLeft(n-1);
    cout << "move " << n << "from middle to right" << endl;
    FromLeftToRight(n-1);
}

void FromMidToLeft(int n)
{
    if(n==1)
    {
        cout << "move 1 from middle to left" << endl;
        return;
     }
    FromMidToRight(n-1);
    cout << "move " << n << "from middle to left" << endl;
    FromRightToLeft(n-1);
}
```