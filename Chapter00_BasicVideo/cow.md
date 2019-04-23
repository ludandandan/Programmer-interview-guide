## 母牛:cow:问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/cow.cpp)

**题目：**
> 母牛每年生一只母牛，新出生的母牛三年后也能每年生一只母牛，假设不会死，求N年后母牛的数量。

> 先写出几个初始项：
> 1. 第一年有母牛A。[A] 1
> 2. 第二年母牛A生了母牛B。[A, B(A)] 2 
> 3. 第三年母牛A生了母牛C，同时母牛A, B 会保留下来。[A, B(A), C(A)] 3
> 4. 第四年母牛A生了母牛D，同时A, B, C会保留下来。[A, B(A), C(A), D(A)] 4 
> 5. 第五年母牛A生了母牛E，母牛B成熟了生了母牛F，同时母牛A,B,C,D会留下了[A, B(A), C(A), D(A), E(A), F(B)] 6
> 6. 第六年母牛A，B，C生了母牛G(A), H(B), I(C)，第五年的牛都会留下了[A, B(A), C(A), D(A), E(A), F(B), G(A), H(B), I(C)] 9
>
>总结规律：F(n) = F(n-1) + F(n-3)。 今年的牛有两个来源，去年的牛F(n-1)都会留下来，三年前的牛可以每牛生一只牛共新生F(n-3)只。
> 解题时先写出几个初始项，然后再用公式进行递归。时间复杂度O(N)。

```c++
int cow(int n)
{
    if(n==0) return 0;
    if(n==1) return 1;
    if(n==2) return 2;
    if(n==3) return 3;
    if(n==4) return 4;
    return cow(n-1)+cow(n-3);
}
```