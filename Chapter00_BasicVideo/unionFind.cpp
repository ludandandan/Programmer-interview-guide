#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;

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

int main()
{
/*
    Node A1 = 1;
    Node A2 = 2;
    Node A3 = 3;
    Node A4 = 4;
    Node A5 = 5;
*/
    Node A1(1,0);
    Node A2(2,1);
    Node A3(3,2);
    Node A4(4,3);
    Node A5(5,4);
    Node A6(5,5);
    vector<Node> nodes;
    nodes.push_back(A1);
    nodes.push_back(A2);
    nodes.push_back(A3);
    nodes.push_back(A4);
    nodes.push_back(A5);
    nodes.push_back(A6);

    unordered_map<Node, Node> map1;
    map1.insert({A1, A2});

    UnionFindSet myset;
    myset.makeSets(nodes);
    //合并
    myset.myUnion(A1, A2);
    cout << myset.isSameSet(A1, A2) << endl;
    cout << myset.isSameSet(A2, A3) << endl;
    myset.myUnion(A2, A5);
    cout << myset.isSameSet(A1, A5) << endl;
    cout << myset.isSameSet(A1, A6) << endl;

    return 0;

}

