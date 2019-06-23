#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <deque>
using namespace std;

class Solution{
public:
    int getValue(string str)
    {
        vector<int> res = value(str, 0);
        return res[0];
    }
    //递归计算括号里面的, 返回括号里面的值和下一步要计算的位置
    vector<int> value(string str, int i)
    {
        //对str从i位置开始计算
        int pre = 0;//数字
        vector<int> bra(2);//要返回的值
        deque<string> deq; //双端队列
        while(i!=str.size() && str[i]!=')')
        {
            //若是遇到数字，就统计在Pre里
            if(str[i]>='0' && str[i]<='9')
            {
                int tmp = str[i++]-'0';
                pre = pre*10+tmp;
            }
            //若是遇到的是+-*/符号，那么将数字pre添加到双端队列里
            //（添加之前需要看看队列里面打头的是否是乘除，若是需要先计算后放进去）
            //然后把刚刚遇到的符号添加到双端队列里
            //然后把pre清零，准备下一次用
            else if(str[i]!='(')
            {
                addNum(deq, pre);//把数字添加到deq
                //把符号添加进去，从尾部
                string tmp;
                tmp += str[i++];
                deq.push_back(tmp);
                pre = 0;
            }
            //若是遇到了左括号，需要递归调用自己
            else
            {
                vector<int> b = value(str, i+1);//返回的是算到的右括号位置或结尾位置
                i = b[1]+1;
                pre = b[0];
            }
        }
        //最后一个Pre没有符号引导进入deq，所以需要单独添加
        addNum(deq, pre);
        bra[0] = getNum(deq); //只处理加减
        bra[1] = i; //到右括号或结尾
        return bra;
    }

    //addNum需要先看看deq的尾部的符号是否是乘除，若是需要先计算，若不是直接将Num扔进去
    void addNum(deque<string> &deq, int num)
    {
        if(!deq.empty())
        {
            string tail = deq.back(); //从尾部取出看看是否是乘除
            if(tail=="*" || tail=="/")
            {
            //若是乘除，需要先把后面两个拿出来
                deq.pop_back();
                int cur = stoi(deq.back());//数字
                deq.pop_back();
                num = tail=="*"? cur*num: cur/num;
            }
        }
        //若不是乘除，那么直接将数字填进去
        deq.push_back(to_string(num));
    }

    //deq里只有加减，开始计算，从左到右
    int getNum(deque<string> &deq)
    {
        int res = 0;
        bool add = true;
        string cur;
        int num = 0;
        while(!deq.empty())
        {
            cur = deq.front();
            deq.pop_front();
            if(cur=="+")
            {
                add = true;
            }
            else if(cur=="-")
            {
                add = false;
            }
            else
            {
                //若是数字
                num = stoi(cur);
                res += add?num:(-num);
            }
        }
        return res;
    }

};

int main()
{
    string str;
    Solution s;
    cin >> str;
    int res = s.getValue(str);
    cout << res << endl;
    return 0;
}
