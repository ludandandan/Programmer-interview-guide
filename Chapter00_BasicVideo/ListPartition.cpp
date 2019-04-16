#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(nullptr){}
};

ListNode* ListPatition1(ListNode *head, int num);
ListNode* ListPatition2(ListNode *head, int num);
void swap(vector<ListNode*> &arr, int i, int j);

int main()
{
    ListNode A1(1);
    ListNode A2(5);
    ListNode A3(0);
    ListNode A4(9);
    ListNode A5(2);
    ListNode A6(3);

    A1.next = &A2;
    A2.next = &A3;
    A3.next = &A4;
    A4.next = &A5;
    A5.next = &A6;

    //ListNode *head = ListPatition1(&A1, 10);
    ListNode *head = ListPatition2(&A1, 9);
    ListNode *cur = head;
    while(cur!=nullptr)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;
    return 0;
}

ListNode* ListPatition1(ListNode *head, int num)
{
    if(head==nullptr || head->next==nullptr) return head;
    vector<ListNode*> ListPool;
    ListNode *cur = head;
    int n = 0; //链表长度
    while(cur!=nullptr)
    {
        ListPool.push_back(cur);
        cur = cur->next;
        n++; 
    }
    int less = -1;
    int more = n;
    int i = 0;
    while(i<more)
    {
        if(ListPool[i]->val==num) {i++; continue;}
        else if(ListPool[i]->val<num) swap(ListPool, ++less, i++);
        else swap(ListPool, --more, i);
    }

    for(int i=0; i<n-1; i++)
    {
        ListPool[i]->next = ListPool[i+1];   
    }
    ListPool[n-1]->next = nullptr;
    return ListPool[0];

}

void swap(vector<ListNode*> &arr, int i, int j)
{
    ListNode *tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

ListNode* ListPatition2(ListNode *head, int num)
{
    if(head==nullptr || head->next==nullptr) return head;
    ListNode *less = nullptr;
    ListNode *lessEnd = nullptr;
    ListNode *equal = nullptr;
    ListNode *equalEnd = nullptr;
    ListNode *more = nullptr;
    ListNode *moreEnd = nullptr;

    ListNode *cur = head;
    while(cur!=nullptr)
    {
        if(less==nullptr && cur->val<num) less = cur;
        else if(equal==nullptr && cur->val==num) equal = cur;
        else if(more==nullptr && cur->val>num) more = cur;
        cur = cur->next;
    }
    lessEnd = less;
    equalEnd = equal;
    moreEnd = more;

    cur = head;
    while(cur!=nullptr)
    {
        if(cur!=lessEnd && cur->val<num)
        {
            lessEnd->next = cur;
            lessEnd = lessEnd->next;
        }
        else if(cur!=equalEnd && cur->val==num)
        {
            equalEnd->next = cur;
            equalEnd = equalEnd->next;
        }
        else if(cur!=moreEnd && cur->val>num)
        {
            moreEnd->next = cur;
            moreEnd = moreEnd->next;
        }
        cur = cur->next;
    }

    //连起来
    if(lessEnd!=nullptr)
    {
        lessEnd->next = equal;
        //接下来该相等区域的尾巴连大于区域的头，若相等区域没有，
        //那么就让相等区域的尾巴变为小于区域的尾巴，
        //到时让小于区域的尾巴去连大于区域的头
        equalEnd = equalEnd==nullptr?lessEnd:equalEnd;
    }
    if(equalEnd!=nullptr)
    {
        equalEnd->next = more;
    }
    if(moreEnd!=nullptr)
    {
        moreEnd->next = nullptr;
    }
    return less!=nullptr?less:equal!=nullptr?equal:more;
}
