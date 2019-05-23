#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

class Solution{
public:
    void rotateWord(vector<char> &chas)
    {
        if(chas.empty() || chas.size()==1) return;
        //将chas整体反转
        reverse(chas.begin(), chas.end());
        //对每个单词再反转
        int i=0;
        int n=chas.size();
        int start = 0;//一个单词的起始位置
        int end = 0;//一个单词的结束位置
        while(i<n)
        {
            while(i<n && chas[i]==' ') i++;
            vector<char> tmp;
            start = i;
            end = i;
            while(i<n && chas[i]!=' ')
            {
                i++;
                end++;//反转的时候用到end-1
            }
            reverseWord(chas, start, end-1);
        }
    }
    void reverseWord(vector<char> &chas, int start, int end)
    {
        //将chas中[start,...,end]的字符反转过来
        int i = start;
        int j = end;
        while(i<j)
        {
            swap(chas, i++, j--);
        }
    }

    void swap(vector<char> &chas, int i, int j)
    {
        char tmp = chas[i];
        chas[i] = chas[j];
        chas[j] = tmp;
    }
    void rotateWord(string &chas)
    {
        if(chas.empty() || chas.size()==1) return;
        //将chas整体反转
        reverse(chas.begin(), chas.end());
        //对每个单词再反转
        int i=0;
        int n=chas.size();
        int start = 0;//一个单词的起始位置
        int end = 0;//一个单词的结束位置
        while(i<n)
        {
            while(i<n && chas[i]==' ') i++;
            vector<char> tmp;
            start = i;
            end = i;
            while(i<n && chas[i]!=' ')
            {
                i++;
                end++;//反转的时候用到end-1
            }
            reverseWord(chas, start, end-1);
        }
    }
    void reverseWord(string &chas, int start, int end)
    {
        //将chas中[start,...,end]的字符反转过来
        int i = start;
        int j = end;
        while(i<j)
        {
            swap(chas, i++, j--);
        }
    }

    void swap(string &chas, int i, int j)
    {
        char tmp = chas[i];
        chas[i] = chas[j];
        chas[j] = tmp;
    }

    void rotate1(string &str, int size)
    {
        reverse(str.begin(), str.end());
        int len = str.size();
        int index = len-size-1;
        reverseWord(str, 0, index);
        reverseWord(str, index+1, len-1);
    }
};

int main()
{
    Solution s;
    vector<char> chas{' ', ' ','d','o','g',' ','l','o','v','e','s',' ','p','i','g','.'};
    s.rotateWord(chas);
    for(char c: chas) cout << c;
    cout << endl;
    string str = "Dog loves pig.";
    s.rotateWord(str);
    cout << str << endl;//对字符串
    string str1 = "ABCDE";
    s.rotate1(str1, 3);
    cout << str1 << endl;
    return 0;
}
