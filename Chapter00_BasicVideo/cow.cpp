#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int cow(int n);

int main()
{
    int res = cow(6);
    cout << res << endl;
    return 0;
}

int cow(int n)
{
    if(n==0) return 0;
    if(n==1) return 1;
    if(n==2) return 2;
    if(n==3) return 3;
    if(n==4) return 4;
    return cow(n-1)+cow(n-3);
}
