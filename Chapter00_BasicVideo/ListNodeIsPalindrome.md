## 判断链表是否为回文结构
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/ListNodeIsPalindrome.cpp)

**题目：**
> 判断一个链表是否为回文结构。给定一个链表的头节点head，请判断这个链表是否为回文结构。例如：1->2->1返回true， 14->3->3->14返回true，1->2->3返回false。
> 
> 进阶：若链表长度为N，是否能做到时间复杂度O(N)，额外空间复杂度O(1)。

> 对于面试和笔试要求不一样。笔试时不太限制空间复杂度，尽快做完题目为好，面试时尽量得到时间复杂度和空间复杂度都小的最优解。对于这个题目有三种方法。


> 方法一：将整个链表逆序，然后一一比对其值。对于逆序，可以使用栈结构实现。将链表的值一一压入栈中，再逐个弹出与链表节点的值比。
```c++
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
```

> 方法二：一半进栈，比方法一节省一半空间，但空间复杂度仍然为O(N)。使用一个fast，一个slow指针找到链表的中间位置（若链表长度为奇数中间位置就是最中间，若链表长度为偶数，中间位置为中间的右边那个）。找到中间位置后将后半段压栈。然后逐个弹出与链表前半段比对。
```c++
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
```

> 方法三：空间复杂度O(1)。不使用栈结构，直接在原位置将后半段反转，前半段的最后一个节点指向空，后半段的第一个节点指向这个节点。反转后，从两头开始比对，直到出现不匹配了或直到有一头到空了为止。注意最后还要将后半段的反转链表恢复。
```c++
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


```