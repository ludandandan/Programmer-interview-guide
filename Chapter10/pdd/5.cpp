#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
 
int main()
{
    int hp, normalAttack, buffedAttack;
    cin >> hp;
    cin >> normalAttack;
    cin >> buffedAttack;
    int res = 0;
    if (buffedAttack <= 2 * normalAttack)  res = ceil(double(hp) / double(normalAttack));
    else
    {
        res = 2*(hp / buffedAttack);
        if (hp%buffedAttack > normalAttack) res += 2;
        else if (hp%buffedAttack > 0) res += 1;
    }
    cout << res << endl;
    return 0;
 
}