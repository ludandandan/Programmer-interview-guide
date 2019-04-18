## 二叉树的序列化和反序列化
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/serial.cpp)

**题目：**
> 二叉树被记录成文件的过程叫做二叉树的序列化，通过文件内容重建原来二叉树的过程叫做二叉树的反序列化。给定一棵二叉树的头节点head，并已知二叉树的节点类型为32位整型。请设计一种二叉树序列化和反序列化的方案并用代码实现。

> 遍历整棵树，然后使用字符串记录节点的值。假设结果字符串为str，初始时为空，若遇到nullptr节点，则在str的末尾加上"#_"，"#"表示这个节点为空，"_"表示一个值的结束，若遇到val为2的节点，则在str的末尾加上"2_"。根据遍历方式不同，有不同的序列化方案，一种序列化方案有其相应的反序列化方案。

> 方案一： 先序遍历序列化和反序列化
> 
> 序列化：有递归和非递归两种方法。
> 
> 递归方法就是先在结果字符串中放根节点的值，然后放左子树得到的结果字符串，然后放右子树得到的结果字符串，终止条件是到空节点，就放"#_"并返回。注意这里将数字转换为字符串用到了to_string()函数。
```c++
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
```
> 非递归方法是在先序遍历非递归版上进行修改。也需要用到栈，只要弹出的当前节点不是空，在结果字符串str后面添加"val_"后，不管左孩子，右孩子是否是空，都把这两个孩子压进去。但若当前节点是空，那么就在结果字符串str后面添加"val_"后，就继续pop栈后面的，并不再进行压栈操作。
```c++
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
```

> 反序列化：由序列化得到的字符串重建出整颗二叉树的过程。
> 
> 首先把一整串的字符串变为vector<string>类型。
```c++
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
```
> 用队列保存这些分割后的字符串，每次需要时就弹出一个来。先序遍历的反序列化用递归方法。递归终止条件是遇到"#"就返回nullptr。先定义根节点，然后建立左子树，然后建立右子树。把string类型转换为数字需要用到stoi()函数。
```c++
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
```

> 方案二：按层遍历的方式进行序列化和反序列化。
>
> 序列化方法一：准备两个队列q和ql，ql用于保存下一层的节点，q用于记录当前层的节点，当q中当前层的节点都用完了，就与ql交换获得下一层的节点，下一层变为当前层。使用队列，从左到右依次压入节点。弹出节点时将节点的值添加到结果字符串中，若当前弹出的节点不为空，在添加"val_"后，就把它的左孩子和右孩子（不管孩子是否为空）放到队列里；若当前节点为空，那么就添加"#_"并且不再往队列里进数，接着弹出下一个节点。
```c++
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
```
> 按层序列化方法二：此方法是书中的方法。准备一个队列，只进有val的node，不进nullptr。进之前在结果字符串中添加 "val_" 或 "#_"。（方法一是出来队列后添加，并且是有值的和 Nullptr都进队列）。若当前节点的左孩子不为空，那么将左孩子值添加进结果字符串，左孩子进队列。若左孩子为空，那么结果字符串中添加 "#_"。然后再看右孩子。
```c++
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
```

>按层反序列化：先将字符串分割，然后根据vector<string>的第一个元素建立根节点。准备一个队列，这个根节点进队列。从队列中弹出的当前节点，先建立其左孩子（当是"#_"时就为空），若左孩子不为空就进队列，然后建立其右孩子，若右孩子不为空就进队列，进队列以便以后出来再连接它自己的左孩子和右孩子。反正就是先左再右，出队列的时候也是先左再右，因为按层遍历就是先左再右遍历的。还需要一个int类型的变量来记录消费到哪个字符串了。

```c++
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
```