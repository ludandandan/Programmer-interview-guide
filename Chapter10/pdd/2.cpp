#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;
 
int main()
{
    string s1, s2;
    cin >> s1;
    cin >> s2;
    int n1 = s1.size();
    int n2 = s2.size();
    vector<int> resv(n1 + n2, 0);
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    for (int i1 = 0; i1 <n1; i1++)
    {
        for (int i2 = 0; i2 <n2; i2++)
        {
            int p1 = i1 + i2; //低位
            int p2 = i1 + i2 + 1; //高位
            int num1 = s1[i1] - '0';
            int num2 = s2[i2] - '0';
            int mul = num1 * num2;
            resv[p1] += mul;
            resv[p2] += resv[p1] / 10;
            resv[p1] = resv[p1] % 10;
        }
    }
    string res;
    for (int i = 0; i < resv.size()-1; i++)
    {
        char c = resv[i] + '0';
        res = c + res;
    }
    if (resv[resv.size() - 1] != 0)
    {
        char c = resv[resv.size() - 1] + '0';
        res = c + res;
    }
    cout << res << endl;
    getchar();
    return 0;
}