#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

class TrieNode{
public:
    int path;
    int end;
    TrieNode* next[26]={nullptr};
    TrieNode():path(0), end(0){}
};
class TrieTree{
/*   
public:
    class TrieNode{
    public:
        int path;
        int end;
        TrieNode* next[26]={nullptr};
        TrieNode():path(0), end(0){}
    };
*/
private:
    TrieNode root;
    vector<char> split(string s)
    {
        vector<char> vc;
        if(s.empty()) return vc;
        istringstream is(s);
        char ch;
        while(is>>ch)
        {   
            vc.push_back(ch);
        }
        return vc;
    }   
public:
     void insert(string word)
    {
        if(word.empty()) return;
        // 把word中的每个字母放到数组中
        vector<char> vc = split(word);
        //建头
        TrieNode *node=&root; //必须是指针指向地址，这样node变root才跟着变
        for(auto c:vc)
        {
            int path_index = c-'a';
            if(node->next[path_index]==nullptr)
            {
                node->next[path_index] = new TrieNode;
            }
            node = node->next[path_index];//指针解引用
            node->path++;
        }
        node->end++;
    }

    int search(string word)
    {
        if(word.empty()) return 0;
        vector<char> vc = split(word);
        TrieNode *node = &root;
        for(auto c:vc)
        {
            int path_index = c -'a';
            if(node->next[path_index]==nullptr) return 0;
            node = node->next[path_index];
        }
        return node->end;
    }

    void mydelete(string word)
    {
        if(search(word)!=0)
        {
            vector<char> vc = split(word);
            TrieNode *node = &root;
            for(auto c:vc)
            {
                int path_index = c - 'a';
                node = node->next[path_index];
                node->path--;
                if(node->path==0)
                {
                    node = nullptr;
                    return;
                }
            }
            node->end--;
        }
    }

    int prefixNumber(string pre)
    {
        if(pre.empty()) return 0;
        vector<char> vc = split(pre);
        TrieNode *node = &root;
        for(auto c:vc)
        {
            int path_index = c - 'a';
            if(node->next[path_index]==nullptr) return 0;
            node = node->next[path_index];
        }
        return node->path;
        
    }
};



int main()
{
/*
    TrieNode t;
    t.path++;
    t.end++;
    if(t.next[0]==nullptr) cout << "qqqqqqqqqqq";
    t.next[0] = new TrieNode;
    if(t.next[0]==nullptr) cout << "aaaaaaa";
    cout << t.path << endl;
*/
    TrieTree t;
    t.insert("abc");
    t.insert("abc");
    t.insert("abc");
    t.insert("ab");
    cout << t.prefixNumber("ab") << endl;
    cout << t.search("abc") << endl;
    t.mydelete("abc");
    cout << t.search("abc") << endl;
    cout << t.search("ab") << endl;
    t.mydelete("ab");
    cout << t.search("ab") << endl;
    cout << t.prefixNumber("ab") << endl;
    cout << t.search("a") << endl;
    return 0;

}
