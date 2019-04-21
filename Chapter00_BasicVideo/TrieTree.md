## 前缀树的实现
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/TrieTree.cpp)

**题目：**

[学习前缀树链接](https://www.cnblogs.com/luosongchao/p/3239521.html)

[前缀树的应用链接](https://blog.csdn.net/v_july_v/article/details/6685962)
> 前缀树是一种树形结构，但不是二叉树。它用于统计大量的字符串。
> 设计的前缀树要有以下三个功能:
>  1. 插入一个字符串
>  2. 搜索树中某个字符串的个数（在每个节点添加数据线end，用于记录有多少字符串是以这个节点结尾的）
> `3. 从树中删除某个字符串
>  4. 检查树中有多少字符串是以某字符串开头的。（在每个节点添加数据项path，用于记录每个节点被划过几次）
>  
> 建树的时候节点上不放字符，在节点与节点之间的路径上填上字符。比如将字符串"abc"加入到树中，先把字符串中每个字符放到vector容器中，逐个操作。那么会检查从头节点开始的表示a的路径的另一端有没有节点，如果没有，那么就在a路径后面加上一个节点。然后a路径就通了，新添加的节点path++，表示这个节点被划过一次。然后看看从a到b的节点有没有，没有就添加否则就直接Path++，最后看看从b到c的节点有没有，没有就添加否则就直接path++，并且同时end++。
> 
> 当搜索树中某字符串的个数时，同样先把字符串的字符放到vector容器中，然后逐个操作，到某个路径若是没有下一个节点了那么就直接返回0，若是找到最后一个字符了，那么从相应的节点中拿出它的end来，就是要返回的值。
>
> 当要删除树中的某个字符串时，若是这个字符串在树中出现了两次，那么只需path--，end--。但是若是path只剩1了，那么再--就变为0了，那么这个节点后面的节点也不会有了，直接将这个节点设置为nullptr，然后返回就Ok，也不需要end--了。
> 
>检查树中有多少字符串是以某字符串开头的。当检查完这个字符串后返回最后那个节点的path即可

```c++
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


```