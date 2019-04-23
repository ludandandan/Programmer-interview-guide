#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

void printAllSubsquences(string str);
void process(string str, string res, int i);

int main()
{
    string str{"abc"};
    printAllSubsquences(str);
    return 0;
}

void printAllSubsquences(string str)
{
    if(str.empty()) return;
    string res;
    process(str, res, 0);
}

void process(string str, string res, int i)
{
    if(i==str.size()) 
    {
        cout << res << endl;
        return;
    }
    process(str, res, i+1);
    process(str, res+str[i], i+1);
}
