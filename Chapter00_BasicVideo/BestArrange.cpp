#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;


struct program{
    int start;
    int end;
    program(int s, int e): start(s), end(e){}
};

bool endEarly(program *p1, program *p2)
{
    return (p1->end) < (p2->end);
}
int bestArrange(vector<int> start, vector<int> end);
int bestArrange(vector<program*> vp, int cur);


int main()
{
    vector<int> start{5,6,7,8,10,11,7};
    vector<int> end{8,7,9,9,12,13,8};

    int res = bestArrange(start, end);
    cout << res << endl;

    return 0;
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


