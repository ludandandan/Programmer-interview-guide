#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

int factorial(int n);
int factorialRecur(int n);

int main()
{
    int res = factorial(5);
    cout << res << endl;
    int resR = factorialRecur(5);
    cout << resR << endl;
    return 0;
}

int factorial(int n)
{
    if(n==0) return 1;
    if(n==1) return 1;
    int res = 1;
    for(int i=1; i<=n; i++)
    {
        res = res*i;
    }
    return res;
}

int factorialRecur(int n)
{
    if(n==0) return 1;
    if(n==1) return 1;
    return n*factorialRecur(n-1);
}
