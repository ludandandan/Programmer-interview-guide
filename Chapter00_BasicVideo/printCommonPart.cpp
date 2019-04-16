#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(nullptr){}
};

void printCommonPart(ListNode *head1, ListNode *head2);

int main()
{
    ListNode A1(1);
    ListNode A2(2);
    ListNode A3(3);
    ListNode A4(4);
    ListNode A5(6);

    ListNode B1(0);
    ListNode B2(2);
    ListNode B3(3);
    ListNode B4(6);
    ListNode B5(7);
    
    A1.next = &A2;
    A2.next = &A3;
    A3.next = &A4;
    A4.next = &A5;
    B1.next = &B2;
    B2.next = &B3;
    B3.next = &B4;
    B4.next = &B5;

    printCommonPart(&A1, &B1);
    return 0;
}

void printCommonPart(ListNode *head1, ListNode *head2)
{
    if(head1==nullptr || head2==nullptr) return;
    while(head1!=nullptr && head2!=nullptr)
    {
        if(head1->val<head2->val) head1 = head1->next;
        else if(head1->val>head2->val) head2 = head2->next;
        else 
        {
            cout << head1->val << " ";
            head1 = head1->next;
            head2 = head2->next;
        }
    }
}
