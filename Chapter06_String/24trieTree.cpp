#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

class trieNode{
public:
    int path;
    int end;
    trieNode *next[26];
    trieNode():path(0),end(0){}
};

class trieTree{
public:
    trieNode *root = new trieNode();

    //查找
    bool search(string word)
    {
        if(word.empty()) return false;
        trieNode *cur = root;
        for(int i=0; i<word.size(); i++)
        {
            int n = word[i]-'a';
            if(cur->next[n]==nullptr) return false;
            cur = cur->next[n];
        }
        return true;
    }

    //插入
    void insert(string word)
    {
        if(word.empty()) return;
        trieNode *cur = root;
        cur->path++;
        for(int i=0; i<word.size(); i++)
        {
            int n = word[i]-'a';
            if(cur->next[n]==nullptr)
            {
                cur->next[n] = new trieNode();
            }
            cur = cur->next[n];
            cur->path++;
        }
        cur->end++;
    }

    //删除
    void mydelete(string word)
    {
        if(search(word))
        {
            trieNode* cur = root;
            cur->path--;
            for(int i=0; i<word.size(); i++)
            {
                int n = word[i]-'a';
                if(cur->next[n]->path==1)
                {
                    cur->next[n] = nullptr;
                    return;
                }
                else
                {
                    cur = cur->next[n];
                    cur->path--;
                }
            }
            cur->end--;
        }
    }

    int prefixNumber(string pre)
    {
        if(pre.empty()) return 0;
        trieNode *cur = root;
        for(int i=0; i<pre.size(); i++)
        {
            int n = pre[n]-'a';
            if(cur->next[n]==nullptr) return 0;
            cur = cur->next[n];
        }
        return cur->path;
    }
};

int main()
{
    trieTree t;
    cout << t.search("abc") << endl;
    t.insert("abcd");
    cout << t.search("abc") << endl;
    t.insert("abc");
    t.insert("d");
    cout << t.search("abc") << endl;
    t.mydelete("abcd");
    cout << t.search("abc") << endl;
    cout << t.search("abcd") << endl;
    return 0;
}
