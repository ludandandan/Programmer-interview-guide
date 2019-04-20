## 实现并查集
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/unionFind.cpp)

**题目：**
> 实现并查集结构。并查集结构是一种用来管理元素分组情况的数据结构。可以高效的进行如下操作：
> 1. 查询元素a与元素b是否属于同一组。
> 2. 合并元素a和元素b所在的组。
> 3. 并查集结构需要初始化时将所有样本一次性的给它。


> 并查集结构是用树形结构来实现的，不过不是二叉树。每个元素对应一个节点，每个组对应一棵树。每一组有一个代表节点。代表节点的父是它自己。若两个节点的代表节点一致，那么他们属于同一组。
> 可以用两个哈希表来实现并查集结构。一个哈希表的key是某节点，value是这个节点父，叫做fatherMap。一个哈希表的key是某节点，value是这个节点所在集合的元素个数，叫做sizeMap。在sizeMap中可以只保留代表节点，因为一组数的所有节点的size都相同。
> 1. 查询：查询两个节点是否属于同一组，可以先向上找到这两个节点的代表节点，代表节点相同的节点属于同一组。
> 2. 合并：将两个节点a，b所在集合合并。需先向上找到这两个节点的代表节点heada和headb，若两代表节点相同，那么就已经是同一集合，无需合并。否则，就拿出这两个代表节点的size来比较，把短的挂在长的上，就是把短的的代表节点的父设置为长的的代表节点。
> 3. 如何这一个节点的代表节点？这个节点一直向上找，找到一个节点，它的父就是它自己，那么这个节点就是这个集合的代表节点。有一个小优化是，在向上找的过程中在一个栈里将沿途的节点记录下来，然后把栈里的节点的父都直接设置为它的代表节点，那么下一次找的时候可以节省时间。

> 这个题本身不是很难，对我来说难的是建这个Node结构，并且要让他进入hashMap中。必须重载==,!=,<这些符号，只有一个val类型的Node我还没弄明白怎么搞，要是以这个node的内存地址作为比较又老是报错，要是直接以val进行比较，那么两个不同节点若值相同就算是同一个节点了，如果这一点可以接受的话，可以直接将Node定义为基础类型，这样简单，只需加上第46行的typedef int Node;就可以了，以后对string等类型操作直接将int该为Node就行。目前是加了一个key作为每个节点独一无二的标记，以后学会了更好的再改。

```c++
// 实际上就是int，当然也可以变为其他类型。
struct Node{
    int val;
    int key = 0;
    Node(int x=0, int y=0): val(x), key(y){};
    friend bool operator < (const Node &node1, const Node &node2);
    friend bool operator == (const Node &node1, const Node &node2);
    friend bool operator != (const Node &node1, const Node &node2);
};

inline bool operator < (const Node &node1, const Node &node2)
{
    return node1.key<node2.key;
}

inline bool operator == (const Node &node1, const Node &node2)
{
    return node1.key==node2.key;
}
inline bool operator != (const Node &node1, const Node &node2)
{
    return node1.key!=node2.key;
}

namespace std{
template<>
struct hash<Node>
{
    size_t operator() (const Node &node) const
    {
        return hash<int>()(node.val)^hash<int>()(node.key);
    }
};
}

// typedef int Node;
class UnionFindSet{
private:
    unordered_map<Node, Node> fatherMap;
    unordered_map<Node, int> sizeMap;
public:
    void makeSets(vector<Node> nodes)
    {
        //fatherMap.clear();
        //sizeMap.clear();
        for(auto node: nodes)
        {
            fatherMap.insert({node, node});
            sizeMap.insert({node, 1});
        }
    }
    
    Node findHead(Node node)
    {
        //找到头节点并且沿途的节点都变扁平。
        Node father = fatherMap[node];
        stack<Node> s;
        while(father!=node)
        {
            s.push(node);
            node = father;
            father = fatherMap[node];
        }
        while(!s.empty())
        {
            Node cur = s.top();
            s.pop();
            fatherMap[node] = father;
        }
        return father;
    }

    bool isSameSet(Node node1, Node node2)
    {
        Node head1 = findHead(node1);
        Node head2 = findHead(node2);
        return head1==head2;
    }

    void myUnion(Node node1, Node node2)
    {
        Node head1 = findHead(node1);
        Node head2 = findHead(node2);
        if(head1==head2) return;
        int size1 = sizeMap[head1];
        int size2 = sizeMap[head2];
        if(size1>size2)
        {
            fatherMap[head2] = head1;
            sizeMap[head1] = size1+size2;
        }
        else
        {
            fatherMap[head1] = head2;
            sizeMap[head2] = size1+size2;
        }
    }
};
```
