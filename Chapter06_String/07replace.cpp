#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

class Solution{
public:
    void replace(vector<char> &chas)
    {
        if(chas.empty() || chas[0]=='\0') return;
        int len = 0;//左半区的长度
        int num = 0; //左半区的空格数
        int n = chas.size();
        while(chas[len]!='\0')
        {
            if(chas[len]==' ') num++;//先检查是否是空格再对len++
            len++;
        }
        int i = len+num*2-1;
        int j = len-1;
        while(i>=0)
        {
            if(chas[j]==' ')
            {
                chas[i--] = '0';
                chas[i--] = '2';
                chas[i--] = '%';
                j--;
            }
            else chas[i--] = chas[j--];
        }
    }


    void modify(string &s)
    {
        if(s.empty() || s.size()==1) return;
        int n = s.size();
        int i = n-1;//处理到哪个位置
        int j = n-1; //复制到哪个位置
        while(i>=0)
        {
            if(s[i]!='*') 
            {
                s[j--] = s[i--];
            }
            else i--;
        }
        while(j>=0)
        {
            s[j--] = '*';
        }
    }
};

int main()
{
    Solution s;
    vector<char> chas{' ', 'a', ' ', 'b',' ', ' ', 'c', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    s.replace(chas);
    for(char c: chas) cout << c;
    cout << endl;
    string str = "123*8****4";
    s.modify(str);
    cout << str << endl;
    cout << endl;
}
