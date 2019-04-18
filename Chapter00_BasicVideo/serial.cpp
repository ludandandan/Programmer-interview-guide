#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <stack>
#include <sstream>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

string serialByPre(TreeNode *root);
string serialByLevel(TreeNode *root);
string serialByLevel1(TreeNode *root);
TreeNode* ReconByPreString(string preStr);
TreeNode* ReconByLevelString(string levelStr);
TreeNode* generateNodeByString(string s);
void InOrderTraversal(TreeNode *root);
void split(string s, vector<string> &sv, char delim);
TreeNode* ReconByPre(queue<string> &q); //记住要有这个引用，因为每次都是从一个q中往外pop

int main()
{
    TreeNode A1(1);
    TreeNode A2(2);
    TreeNode A3(3);
    TreeNode A4(4);
    TreeNode A5(5);

    A1.left = &A2;
    A1.right = &A3;
    A2.left = &A4;
    A3.right = &A5;

    string preStr = serialByPre(&A1);
    cout << "serial by preorder: " << preStr << endl;
    string levelStr = serialByLevel(&A1);
    cout << "serial by level: " << levelStr << endl;
    string levelStr1 = serialByLevel(&A1);
    cout << "serial by level: " << levelStr << endl;
    //vector<string> sv;
    //split(preStr, sv, '_');
    //for(auto w:sv)
    //{
    //    cout << w << " ";
    //}
    TreeNode *root = ReconByPreString(preStr);
    cout << "recon by pre:" << endl;
    InOrderTraversal(root); //4,2,1,3,5
    cout << endl;
    root = ReconByLevelString(levelStr);
    cout << "recon by level:" << endl;
    InOrderTraversal(root);
    cout << endl;
    return 0;
}

//中序遍历，为了验证
void InOrderTraversal(TreeNode *root)
{
    if(root==nullptr) return;
    stack<TreeNode*> s;
    TreeNode *cur = root;
    while(!s.empty() || cur!=nullptr)
    {
        if(cur!=nullptr)
        {
            s.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = s.top();
            s.pop();
            cout << cur->val << " ";
            cur = cur->right;
        }
    }
}
//先序遍历序列化的递归版
string serialByPre(TreeNode *root)
{
    string res;
    if(root==nullptr)
    {
        return "#_";
    }
    res = to_string(root->val) + "_";
    res += serialByPre(root->left);
    res += serialByPre(root->right);
    return res;
}

//先序遍历序列化的非递归版
string serialByPre1(TreeNode *root)
{
    string res;
    if(root==nullptr)
    {
        res = "#_";
        return res;
    }
    stack<TreeNode*> s;
    TreeNode *cur = root;
    s.push(cur);
    while(!s.empty())
    {
        cur = s.top();
        s.pop();
        if(cur==nullptr) 
        {
            res += "#_";
            continue;//如果当前是空了，那么就停止压栈，
            //只要当前不是空，就压栈，这样就会把叶节点的左右孩子压进去。
        }
        res = res + to_string(cur->val) +"_";
        s.push(cur->right);
        s.push(cur->left);
    }
    return res;
}

//先序遍历的反序列化
TreeNode* ReconByPreString(string preStr)
{
    vector<string> sv;
    split(preStr,sv,'_');
    queue<string> q;
    for(auto w:sv) 
    {
        q.push(w);   
    }
    TreeNode* root = ReconByPre(q);
    return root;
}

TreeNode* ReconByPre(queue<string>& q) //一定要是引用
{
    string s = q.front();
    q.pop();
    if(s=="#") return nullptr;
    TreeNode *root = new TreeNode(stoi(s));
    root->left = ReconByPre(q);
    root->right = ReconByPre(q);
    return root;
}
// 字符分割函数
void split(string s, vector<string>& sv, char delim)
{
    istringstream is(s);
    string tmp;
    while(getline(is, tmp, delim))
    {
        sv.push_back(tmp);
    }
}

// 按层序列化
string serialByLevel(TreeNode *root)
{
    if(root==nullptr) return "#_";
    queue<TreeNode*> q, lq;
    string res;
    q.push(root);
    while(!q.empty())
    {
        TreeNode *cur = q.front();
        q.pop();
        if(cur==nullptr)
        {
            res += "#_";
            continue;
        }
        res = res + to_string(cur->val) + "_";
        lq.push(cur->left);
        lq.push(cur->right);
        if(q.empty()) swap(lq, q);
    }
    return res;
}
// 按层序列化的另一种代码实现方法
string serialByLevel1(TreeNode *root)
{
    if(root==nullptr) return "#_";
    string res;
    res = res + to_string(root->val) + '_';
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty())
    {
        TreeNode *cur = q.front();
        q.pop();
        if(cur->left!=nullptr)
        {
            res = res + to_string(cur->left->val) + '_';
            q.push(cur->left);
        }
        else res += "#_";
        if(cur->right!=nullptr)
        {
            res = res + to_string(cur->right->val) + '_';
            q.push(cur->right);
        }
        else res += "#_";
    }
    return res;
}
TreeNode* ReconByLevelString(string levelStr)
{
    if(levelStr=="#_") return nullptr;
    vector<string> vs;
    split(levelStr, vs, '_');
    queue<TreeNode*> q;
    int index = 0;
    TreeNode *root = generateNodeByString(vs[index++]);
    q.push(root);
    while(!q.empty())
    {   
        TreeNode *cur = q.front();
        q.pop();
        cur->left = generateNodeByString(vs[index++]);
        cur->right = generateNodeByString(vs[index++]);
        if(cur->left!=nullptr) q.push(cur->left);
        if(cur->right!=nullptr) q.push(cur->right);
    }
    return root;
}
TreeNode* generateNodeByString(string s)
{
    if(s=="#") return nullptr;
    TreeNode *node = new TreeNode(stoi(s));
    return node;
}
