#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int islands(vector<vector<int>> m);
void infect(vector<vector<int>> &m, int i, int j, int r, int c);

int main()
{
    vector<vector<int>> m = {
    {0,0,1,0,1,0},
    {1,1,1,0,1,0},
    {1,0,0,1,1,0},
    {0,0,0,0,0,1}
    };

    int res = islands(m);
    cout << res << endl;
    return 0;
}

int islands(vector<vector<int>> m)
{
    if(m.empty() || m[0].empty()) return 0;
    int r = m.size();
    int c = m[0].size();
    int res = 0;
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            if(m[i][j]==1)
            {
                infect(m, i, j, r, c);
                res++;
            }
        }
    }
    return res;
}

void infect(vector<vector<int>> &m, int i, int j, int r, int c)
{
    if(i<0 || i>=r || j<0 || j>=c || m[i][j]!=1) return;
    m[i][j] = 2;
    infect(m, i+1, j, r, c);
    infect(m, i-1, j, r, c);
    infect(m, i, j+1, r, c);
    infect(m, i, j-1, r, c);
}
