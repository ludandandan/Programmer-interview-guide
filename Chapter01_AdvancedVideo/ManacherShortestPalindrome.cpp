#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class solution{
public:
    vector<char> ManacherString(string str)
    {
        int n = str.size();
        vector<char> vc(2*n+1);
        int index = 0;
        for(int i=0; i<(2*n+1); i++)
        {
            vc[i] = (i&1)==0?'#':str[index++];
        }
        return vc;
    }
    //在后面加字符并返回加的字符
    string shortestEnd(string str)
    {
        if(str.empty() || str.size()==1) return str;
        vector<char> vc = ManacherString(str);
        int n = vc.size();

        vector<int> pArr(n,1);//最长回文半径
        int pR = -1;//回文最右边界
        int index = -1;
        int maxContainsEnd = -1; //包含最后一个字符的最长回文半径

        for(int i=1; i<n; i++)
        {
            pArr[i] = i<pR?min(pArr[index*2-i], pR-i):1;
            while(((i-pArr[i])>=0) && ((i+pArr[i])<n) && vc[i-pArr[i]]==vc[i+pArr[i]])
            {
                pArr[i]++;
            }
            if(i+pArr[i]>pR)
            {
                pR = i+pArr[i];
                index = i;
            }
            if(pR == n)
            {
                maxContainsEnd = pArr[i];
                break;
            }
        }
        string res;
        int m = str.size();
        for(int i=(m-maxContainsEnd); i>=0; i--) res += str[i];
        return res;
    }
    //在前面加字符并返回整个回文串
    string shortestFront0(string s)
    {
        if(s.empty() || s.size()==1) return s;
        //在前面加字符相当于在反过来的后面加字符
        // resvers
        string res;
        int n = s.size();
        for(int i=n-1; i>=0; i--)
        {
            res += s[i];
        }
        res = shortestEnd(res);
        reverse(res.begin(), res.end());
        res = res+s;
        return res;
    }
    
    string shortestFront(string s)
    {
        if(s.empty() || s.size()==1) return s;
        //通过反转将在前面添加字符变为在后面添加字符，但最后需要添加的字符还是添加在s前面，无需反转了
        string res;
        for(int i=s.size()-1; i>=0; i--)
        {
            res += s[i];
        }
        vector<char> vc = ManacherString(res);
        int n = vc.size();
        vector<int> pArr(n,1);
        int pR = -1;
        int index = -1;
        int maxContainEnd = -1;
        for(int i=1; i<n; i++)
        {
            pArr[i] = i<pR?min(pArr[index*2-i], pR-i):1;
            while(((i-pArr[i])>=0) && ((i+pArr[i])<n) && (vc[i+pArr[i]]==vc[i-pArr[i]]))
            {
                pArr[i]++;
            }
            if((i+pArr[i])>pR)
            {
                pR = i+pArr[i];
                index = i;
            }
            if(pR==n)
            {
                maxContainEnd = pArr[i];
                break;
            }
        }
        int m = s.size();
        res = res.substr(0,m-maxContainEnd+1);
        res = res+s;
        return res;
    }
};


int main()
{
    string str;
    cin >> str;
    solution s;
    string res = s.shortestFront(str);
    cout << res << endl;

    return 0;
}
