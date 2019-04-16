#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr){}
};

bool ListNodeIsPalindrome1(ListNode *head);
bool ListNodeIsPalindrome2(ListNode *head);
bool ListNodeIsPalindrome3(ListNode *head);

int main()
{
    ListNode A1(1);
    ListNode A2(2);
    ListNode A3(3);
    ListNode A4(2);
    ListNode A5(1);
    A1.next = &A2;
    A2.next = &A3;
    A3.next = &A4;
    A4.next = &A5;
    bool res1 = ListNodeIsPalindrome1(&A1);
    bool res2 = ListNodeIsPalindrome2(&A1);
    bool res3 = ListNodeIsPalindrome3(&A1);
    cout << res1 << endl;
    cout << res2 << endl;
    cout << res3 << endl;
    cout << "the ListNode: " << endl;
    ListNode *cur = &A1;
    while(cur!=nullptr)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    return 0;
}
//全部进栈
bool ListNodeIsPalindrome1(ListNode *head)
{
    if(head==nullptr||head->next==nullptr) return true;
    stack<int> s;
    ListNode *cur = head;
    while(cur!=nullptr)
    {
        s.push(cur->val);
        cur = cur->next;
    }
    cur = head;
    while(!s.empty())
    {
        if(cur->val==s.top())
        {
            s.pop();
            cur = cur->next;
        }
        else return false;
    }
    return true;
}


//一半进栈
bool ListNodeIsPalindrome2(ListNode *head)
{
    if(head==nullptr||head->next==nullptr) return true;
    stack<int> s;
    ListNode *fast = head;
    ListNode *slow = head;
    while(fast->next!=nullptr && fast->next->next!=nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    while(slow!=nullptr)
    {
        s.push(slow->val);
        slow = slow->next;
    }
    ListNode *cur = head;
    while(!s.empty())
    {
        if(s.top()!=cur->val) return false;
        else{
            s.pop();
            cur=cur->next;
        }
    }
    return true;
}


//在原来位置反转，不进栈
bool ListNodeIsPalindrome3(ListNode *head)
{
    if(head==nullptr || head->next==nullptr) return true;
    ListNode *fast = head;
    ListNode *slow = head;
    while(fast->next!=nullptr && fast->next->next!=nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    ListNode *cur = slow->next;//反转链表的第一个
    slow->next = nullptr;
    ListNode *prev = slow;
    while(cur!=nullptr)
    {
        ListNode *next = cur->next;//保留后面的连接
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    ListNode *head1 = head;
    ListNode *head2 = prev;
    bool res = true;
    while(head1!=nullptr && head2!=nullptr)
    {
        if(head1->val!=head2->val) 
        {
            res = false;
            break;
        }
        else
        {
            head1 = head1->next;
            head2 = head2->next;
        }
    }

    // 再将反转后的链表反转回来
   cur = prev; //最后一个节点
   prev = nullptr;
   while(cur!=nullptr)
   {
        ListNode *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
   }
   return res;
}

