#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

string LowestLexicography(vector<string> strs);

int main()
{
    vector<string> strs{"ba", "b", "abc", "ac"};
    string res = LowestLexicography(strs);
    cout << res << endl;
    return 0;
}

bool LexicographyAscending(string str1, string str2)
{
    string str12 = str1+str2;
    string str21 = str2+str1;
    return str12 < str21;
}

string LowestLexicography(vector<string> strs)
{
    if(strs.empty()) return NULL;
    sort(strs.begin(), strs.end(), LexicographyAscending);
    string res;
    for(string s:strs)
    {
        res += s;
    }
    return res;

}
