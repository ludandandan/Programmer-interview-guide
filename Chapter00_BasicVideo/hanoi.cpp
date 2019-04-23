#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void hanoi(int n);//3层哈诺塔问题
void process(int n, string from , string to, string help);
//笨方法，定义6个函数彼此嵌套
void FromLeftToRight(int n);
void FromLeftToMid(int n);
void FromRightToLeft(int n);
void FromRightToMid(int n);
void FromMidToLeft(int n);
void FromMidToRight(int n);

int main()
{
    hanoi(3);
    FromLeftToRight(3);
    return 0;
}
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
