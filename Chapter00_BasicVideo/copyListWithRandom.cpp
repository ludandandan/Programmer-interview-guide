#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode *random;
    ListNode(int x):val(x),next(nullptr),random(nullptr){}
};

ListNode* copyListWithRandom1(ListNode *head);
ListNode* copyListWithRandom2(ListNode *head);
ListNode* copyListWithRandom22(ListNode *head);

int main()
{
    ListNode A1(1);
    ListNode A2(2);
    ListNode A3(3);

    A1.next = &A2;
    A2.next = &A3;
    A1.random = &A3;
    A2.random = &A1;
    A3.random = &A2;

    //ListNode *head = copyListWithRandom1(&A1);
    //ListNode *head = copyListWithRandom2(&A1);
    ListNode *head = copyListWithRandom22(&A1);
    ListNode *cur = head;
    while(cur!=nullptr)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    return 0;
}

ListNode* copyListWithRandom1(ListNode *head)
{
    unordered_map<ListNode*, ListNode*> map;
    ListNode *cur = head;
    while(cur!=nullptr)
    {
        ListNode *tmp = new ListNode(cur->val);
        map.insert({cur,tmp});
        cur = cur->next;
    }

    cur = head;
    while(cur!=nullptr)
    {
        map[cur]->next = map[cur->next];
        map[cur]->random = map[cur->random];
        cur = cur->next;
    }
    return map[head];
}

ListNode * copyListWithRandom2(ListNode *head)
{
    if(head==nullptr) return head;
    ListNode *cur = head;
    //建立copy节点并把它放在它的原节点的Next指针上
    while(cur!=nullptr)
    {
        ListNode *tmp = new ListNode(cur->val);
        tmp->next = cur->next;
        cur->next = tmp;
        cur = cur->next->next;
    }
    //连接copy节点的random指针
    cur = head;
    while(cur!=nullptr)
    {
        cur->next->random = cur->random==nullptr?nullptr:cur->random->next;
        cur = cur->next->next;
    }
    //copy节点与原节点分离
    /*//一种方法
    cur = head;
    ListNode *head2 = cur->next;
    ListNode *cur2 = head2;
    while(cur->next->next!=nullptr)
    {
        cur->next = cur2->next;
        cur2->next = cur->next->next;
        cur = cur->next;
        cur2 = cur2->next;
    }
    cur2->next = nullptr;
    cur->next = nullptr;
    */
    //另一种方法
    cur = head;
    ListNode *head2 = cur->next;
    ListNode *cur2 = head2;
    ListNode *next = nullptr;
    while(cur!=nullptr)
    {
        next = cur->next->next;
        cur2 = cur->next;
        cur->next = next;
        cur2->next = next==nullptr?nullptr:next->next;
        cur = next;
    }
    return head2;
}

ListNode* copyListWithRandom22(ListNode *head)
{
    if(head==nullptr) return head;
    //第一次遍历复制节点
    ListNode *cur = head;
    ListNode *curCopy = nullptr;
    ListNode *next = nullptr;
    while(cur!=nullptr)
    {
        next = cur->next; //可能为空
        curCopy = new ListNode(cur->val);
        cur->next = curCopy;
        curCopy->next = next;
        cur = next;
    }

    //第二次遍历设置random指针
    cur = head;
    curCopy = nullptr;
    next = nullptr;
    while(cur!=nullptr)
    {
        curCopy = cur->next;
        curCopy->random = cur->random==nullptr?nullptr:cur->random->next;
        cur = cur->next->next;
    }

    //第三次遍历将两个链表分开
    cur = head;
    ListNode *head2 = head->next;
    curCopy = nullptr;
    next = nullptr;
    while(cur!=nullptr)
    {
        next = cur->next->next; //可能为空
        curCopy = cur->next;
        curCopy->next = next==nullptr?nullptr:next->next;
        cur->next = next;
        cur = next;
    }
    return head2;
}
