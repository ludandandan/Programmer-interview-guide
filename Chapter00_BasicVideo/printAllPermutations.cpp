#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

void printAllPermutations(string str);
void process(string str, int k);
void swap(string &str, int i, int j);

int main()
{
    string str{"abcd"};
    printAllPermutations(str);
    return 0;
}

void printAllPermutations(string str)
{
    process(str, 0);
}

void process(string str, int k)
{
    if(k==str.size())
    {
        cout << str << endl;
        return;
    }
    for(int i=k; i<str.size(); i++)
    {
        swap(str, i, k);
        process(str, k+1);
    }
}


void swap(string &str, int i, int j)
{
    char ch = str[i];
    str[i] = str[j];
    str[j] = ch;
}
