#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr){}
};

ListNode* findFirstIntersectNode(ListNode *head1, ListNode *head2);
ListNode* getFirstLoopNode(ListNode *head);
ListNode* noLoop(ListNode *head1, ListNode *head2);
ListNode* bothLoop(ListNode *head1, ListNode *loop1, ListNode *head2, ListNode *loop2);

int main()
{
    
    ListNode A1(1);
    ListNode A2(2);
    ListNode A3(3);
    ListNode A4(4);
    ListNode A5(5);
    ListNode A6(6);
    ListNode A7(7);
    
    
    // both loop从环的不同位置如环 3/5
    A1.next = &A2;
    A2.next = &A3;
    A3.next = &A4;
    A4.next = &A5;
    A5.next = &A3;

    A7.next = &A6;
    A6.next = &A5;
    

    /*
    // both loop 从环的相同位置入环3
    A1.next = &A2;
    A2.next = &A3;
    A3.next = &A4;
    A4.next = &A5;
    A5.next = &A3;

    A7.next = &A6;
    A6.next = &A3;
    */
    
    /*
    // both loop 两个独立的环
    A1.next = &A2;
    A2.next = &A3;
    A3.next = &A4;
    A4.next = &A2;

    A7.next = &A6;
    A6.next = &A5;
    A5.next = &A7;
    */

    /* 
    //no loop 相交 4
    A1.next = &A2;
    A2.next = &A3;
    A3.next = &A4;
    A4.next = &A5;
    A5.next = &A6;
    
    A7.next = &A4;
    */

    /*
    // no loop 不相交
    A1.next = &A2;
    A2.next = &A3;
    A3.next = &A4;
    
    A7.next = &A6;
    A6.next = &A5;
    */
    ListNode *res = findFirstIntersectNode(&A1, &A7);
    cout << "the first intersect node: " << (res==nullptr?0:res->val) << endl;
    return 0;

}

ListNode* findFirstIntersectNode(ListNode *head1, ListNode *head2)
{
    if(head1==nullptr || head2==nullptr) return nullptr;
    ListNode *loop1 = getFirstLoopNode(head1);
    ListNode *loop2 = getFirstLoopNode(head2);
    
    if(loop1==nullptr && loop2==nullptr) //两个无环链表
    {
        return noLoop(head1, head2);
    }
    else if(loop1!=nullptr && loop2!=nullptr) //两个有环链表
    {
        return bothLoop(head1, loop1, head2, loop2);
    }
    else return nullptr;
}

//使用哈希表判断单链表是否有环并返回第一个入环的节点
ListNode* getFirstLoopNode1(ListNode *head)
{
    if(head==nullptr || head->next==nullptr || head->next->next==nullptr) return nullptr;
    unordered_set<ListNode*> set;
    ListNode *cur = head;
    while(cur!=nullptr)
    {
        auto flag = set.insert(cur);
        if(!flag.second) return cur;
        cur = cur->next;
    }
    return nullptr;
}
//不使用哈希表判断单链表是否有环并返回第一个入环的节点
ListNode* getFirstLoopNode(ListNode *head)
{
    if(head==nullptr || head->next==nullptr || head->next->next==nullptr) return nullptr;
    ListNode *fast = head->next->next;//为了避免第一个判断F与S就相等，初始化时并没有都是head
    ListNode *slow = head->next;
    while(fast!=nullptr && fast->next!=nullptr)
    {
        if(fast==slow) break;
        fast = fast->next->next;
        slow = slow->next;
    }
    if(fast==nullptr || fast->next==nullptr) return nullptr;
    fast = head;
    while(fast!=slow)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}
//哈希表判断两个无环链表是否相交，并返回其相交的第一个节点
ListNode* noLoop1(ListNode *head1, ListNode *head2)
{
    if(head1==nullptr || head2==nullptr) return nullptr;
    unordered_set<ListNode*> set;
    ListNode *cur = head1;
    while(cur!=nullptr)
    {
        set.insert(cur);
        cur = cur->next;
    }
    cur = head2;
    while(cur!=nullptr)
    {
       if(set.find(cur)!=set.end())//找到了
       {
            return cur;
       }
       cur = cur->next;
    }
    return nullptr;
}
// 非哈希表方法判断两个无环链表是否相交，并返回其相交的第一个节点
ListNode* noLoop(ListNode *head1, ListNode *head2)
{
    if(head1==nullptr || head2==nullptr) return nullptr;
    ListNode *end1 = head1;//记录最后一个节点
    int n = 0; //记录长度差
    while(end1->next!=nullptr)
    {
        n++;
        end1=end1->next;
    }
    ListNode *end2 = head2;
    while(end2->next!=nullptr)
    {
        n--;
        end2=end2->next;
    }
    if(end1!=end2) return nullptr;
    ListNode *cur1 = n>0?head1:head2;//长的放在cur1
    ListNode *cur2 = cur1==head1?head2:head1;
    n = abs(n);
    while(n!=0)
    {
        cur1 = cur1->next;
        n--;
    }
    while(cur1!=cur2)
    {
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    return cur1;
}

// 判断两个有环链表是否相交并返回其相交的第一个节点
ListNode* bothLoop(ListNode *head1, ListNode *loop1, ListNode *head2, ListNode *loop2)
{
    if(loop1==loop2)//相交后再共享一个环，与两个无环链表相交方法相同
    {
        int n = 0;
        ListNode *cur1 = head1;
        ListNode *cur2 = head2;
        while(cur1!=loop1)
        {
            cur1 = cur1->next;
            n++;
        }
        while(cur2!=loop2)
        {
            cur2 = cur2->next;
            n--;
        }
        cur1 = n>0?head1:head2;
        cur2 = cur1==head1?head2:head1;
        n = abs(n);
        while(n!=0)
        {
            cur1 = cur1->next;
        }
        while(cur1!=cur2)
        {
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return cur1;
    }
    else
    {
        ListNode *cur = loop1->next;
        while(cur!=loop1)
        {
            if(cur==loop2) return loop1;
            cur = cur->next;
        }
        return nullptr;
    }
}
