#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
 
int main()
{
    int n,m;
    vector<int> h,w;
    cin >> n;
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        h.push_back(num);
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> num;
        w.push_back(num);
    }
    sort(h.begin(), h.end());
    sort(w.begin(), w.end());
    int ph = n - 1;
    int pw = m - 1;
    int res = 0;
    while (ph >= 0 && pw >= 0)
    {
        if (w[pw] >= h[ph])
        {
            res++;
            pw--;
            ph--;
        }
        else
        {
            ph--;
        }
    }
    cout << res << endl;
    getchar();
    return 0;
}