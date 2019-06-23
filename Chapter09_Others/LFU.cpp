#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;

struct Node{
    int key;
    int val;
    int times;
    Node *up;//双端链表，上面的节点
    Node *down;//双端链表，下面的节点
    Node(int x, int y, int z): key(x), val(y), times(z), up(nullptr), down(nullptr){}
};

class NodeList{
public:
    Node *head;//头
    Node *tail;//尾部
    NodeList *last; //双端链表，前面的节点
    NodeList *next; //双端链表，后面的节点
    NodeList(Node *x): head(x), tail(x), last(nullptr), next(nullptr){}
    
    //从尾部添加节点
    void addNodeFromTail(Node *node)
    {
        if(node==nullptr) return;
        //若是当前的nodeList里面是空的，是不可能的
        tail->down = node;
        node->up = tail;
        tail = node; //换尾部
    }

    //检查当前的NodeList是不是空的
    bool isEmpty()
    {
        return head==nullptr;
    }

    //删除一个节点，注意要把这个节点上下重新连接
    void deleteNode(Node *node)
    {
        //node确定在nodeList里面
        if(node==nullptr) return;
        //若是当前就一个节点
        if(head==tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            //若是要删掉的节点是头节点，要换头
            if(node==head)
            {
                head = head->down;
                head->up = nullptr;
            }
            //若是要删掉的节点是尾部，要换尾部
            else if(node==tail)
            {
                tail = tail->up;
                tail->down = nullptr;
            }
            //若是要删掉的节点是中间节点，注意连接
            else
            {
                node->up->down = node->down;
                node->down->up = node->up;
            }
        }
        node->up = nullptr;
        node->down = nullptr;
    }
};

//总的缓存结构
class LFUCache{
public:
    int capacity;//容量
    int size; //当前结构的大小
    unordered_map<int, Node*> records;//根据key查到node
    unordered_map<Node*, NodeList*> heads; //根据node查到nodeList，也就是这个Node属于哪个头
    NodeList *headList; //当超出容量删除节点时要删除头链表的头节点
    LFUCache(int x): capacity(x), size(0), headList(nullptr){}

    //modifyHeadList函数，
    //输入：nodeList类型的removeNodeList, 表示刚刚被删除了一个节点的小链表
    //函数功能是判断这个链表被删掉一个节点后现在是否为空
    //（1）若不是空的，那么什么都不用做
    //（2）若是空的，并且removeNodeList还是整个结构的头链表，那么要删掉这个链表，并换头
    //（3）若是空的，但removeNodeList不是整个结构的头链表，那么要删掉这个链表，并注意连接他左右的链表
    //若是空的，返回值为true，若不是空的返回值为false
    bool modifyHeadList(NodeList *removeNodeList)
    {
        if(removeNodeList->isEmpty())
        {
            if(headList == removeNodeList)//（2）
            {
                headList = removeNodeList->next;
                if(headList!=nullptr)
                {
                    headList->last = nullptr;
                }
            }
            else//（3）
            {
                removeNodeList->last->next = removeNodeList->next;//因为removeNodeList不是头，所以他的last一定不是空
                if(removeNodeList->next!=nullptr)
                {
                    removeNodeList->next->last = removeNodeList->last;
                }
            }
            return true;
        }
        return false;
    }

    //move函数：输入:node, oldNodeList
    //由于Node被访问了，node的times+1了，所以他要脱离他原来的词频链表到新的词频+1的链表里去
    //注意新的链表的左右环境
    //若是oldNodeList在删掉node之后变为空的了，oldNodeList是要被删除的
    //此时，新链表的前一个，将是oldNodeList的前一个
    void move(Node *node, NodeList *oldNodeList)
    {
        //先在老链表中删除节点
        oldNodeList->deleteNode(node);
        NodeList *preList = modifyHeadList(oldNodeList)?oldNodeList->last:oldNodeList;
        NodeList *nextList = oldNodeList->next;
        //检查nextList是否是空的，若是空的，需要自己建一个链表挂在preList后面
        if(nextList==nullptr)
        {
            NodeList *newList = new NodeList(node);
            //左右重新连接
            if(preList!=nullptr) preList->next = newList;
            newList->last = preList;
            if(headList==nullptr) headList = newList;//大结构里只有newList自己
            heads[node] = newList; //更新哈希表的值
        }
        else
        {
            //若NextList不是空，那么检查他的词频与当前节点的词频是否吻合
            //若吻合，直接挂在他的尾部
            if(nextList->head->times==node->times)
            {
                nextList->addNodeFromTail(node);
                heads[node] = nextList; //更新哈希表的值
            }
            else
            {
                //若不吻合，那么需要新建一个链表，加在preList和nextList的中间
                NodeList *newList = new NodeList(node);
                if(preList!=nullptr) preList->next = newList;
                newList->last = preList;
                newList->next = nextList;
                nextList->last = newList;
                if(headList==nullptr) headList = newList;
                heads[node] = newList;
            }
        }
    }

    //题目要求的set操作
    //先检查key是否在record里，若在，那么直接改值，并且更新词频，调整链表
    //若不在，那么需要先新建节点，若cache已经满了，需要先删除后添加
    void set(int key, int value)
    {

        //若是容量为0，那么直接返回
        if(capacity==0) return;
        if(records.count(key)!=0)
        {
            //若是之前有过记录
            //将节点从map中取出来，更新value，和times，调整链表
            Node *node = records[key];
            node->val = value;
            node->times++;
            //将Node从原来词频的链表中取出来，添加到词频加1的链表中
            NodeList *oldNodeList = heads[node];
            move(node, oldNodeList);
        }
        else
        {
            //若是Key从来都没有出现过
            //先检查当前的size有没有到达capacity
            //若是到达了，那么需要先删除headList的头部
            if(size==capacity)
            {
                Node *node = headList->head; //要删除的头部
                headList->deleteNode(node);//从headList中删除
                modifyHeadList(headList); //若是headList空了，那么需要调整
                heads.erase(node); //消除他的影响
                records.erase(node->key);
                size--;
            }
            //添加一个times=1的节点
            //新建一个节点
            Node *node = new Node(key, value, 1);
            //若当前的headList是空，那么新建一个链表，让这个链表里面放Node成为headList
            if(headList==nullptr)
            {
                headList = new NodeList(node);
            }
            //若是不是空
            else
            {
                //检查当前的headList的词频是否是1
                if(headList->head->times==node->times)
                {
                    //若是相等，那么直接挂在尾部
                    headList->addNodeFromTail(node);
                }
                //若当前的headList的词频不是1，那么要新建一个词频为1的NodeList，同时将他换为headList
                else
                {
                    NodeList *newList = new NodeList(node);
                    //将NewList与headlist连接
                    newList->next = headList;
                    headList->last = newList;
                    headList = newList;
                }
            }
            //添加了节点以后要在两个哈希表中添加信息
            //Node的times为1,所以一定是在当前的HeadList里
            records.insert({key, node});
            heads.insert({node, headList});
            size++;
        }
    }

    //题目要求的get操作
    //注意在get操作之后times++，并且要将Node从oldNodeList中取出来，放到新的链表中
    int get(int key)
    {
        //先检查有无这个key,若是没有那么就返回-1表示不存在
        if(records.count(key)==0)
        {
            return -1;
        }
        Node *node = records[key];
        int value = node->val; //用于返回的值
        node->times++;
        NodeList *oldNodeList = heads[node];
        move(node, oldNodeList);
        return value;
    }
};


int main()
{
    LFUCache l(0);
    /*
    l.set(1,1);
    l.set(2,2);
    cout << l.get(1) << endl;
    l.set(3,3);
    cout << l.get(2) << endl;
    cout << l.get(3) << endl;
    l.set(4,4);
    cout << l.get(1) << endl;
    cout << l.get(3) << endl;
    cout << l.get(4) << endl;
    */
    l.set(0,0);
    cout << l.get(0) << endl;
    return 0;
}
