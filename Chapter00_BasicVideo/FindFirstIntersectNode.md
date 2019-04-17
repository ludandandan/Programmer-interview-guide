## 两个单链表相交的一系列问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/FindFirstIntersectNode.cpp)

**题目：**
> 在本题中，单链表可能有环也可能无环。给定两个单链表的头节点head1和head2，这两个单链表可能相交也可能不相交。请实现一个函数，如果两个链表相交，请返回相交的第一个节点N，如果不相交，请返回nullptr。
>
> 要求：如果链表1的长度为N，链表2的长度为M，请达到时间复杂度O(N)，空间复杂度O(1)。

> 这个题目可以分为以下三个问题：
> 1. 如何判断一个单链表是有环还是无环，当有环时返回第一个入环的节点。
> 2. 对于两个无环单链表，如何判断其是否相交，相交时返回第一个相交的节点。
> 3. 对于两个有环单链表，如何判断其是否相交，相交时返回第一个相交的节点。
> 4. 对于一个有环单链表和一个无环单链表是不可能相交的。
>
> 总体的函数框架入下：
```c++
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
```

> 首先解决第一个问题：如何判断一个单链表是有环还是无环，当有环时返回第一个入环的节点。
> 
>   有两种方法，一种使用哈希表实现，空间复杂度O(N)；一种不使用哈希表，而是使用一快一慢两个指针，空间复杂度O(1)。
> 
>方法一：使用哈希表。
>
>把链表中的节点逐个插入到hashset中，使用insert()方法，其返回值的第二个参数若为false表示哈希表中已经存在过这个节点，不能插入进去。第一个出现false的节点就是第一个入环的节点。若链表中的节点都插入进去了都没有false，那么就是无环的了。
```c++
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
``` 

>方法二：不使用哈希表，而是使用一快一慢两个指针。
>准备两个指针F和S，F每次走两步，S每次走一步。若F走到了空，就说明没有环。若有环，F和S一定会在环上相遇。此时，将F重新放到头节点的位置，与S一起，一次走一步，F与S第一次相遇的位置就是入环的第一个节点。
```c++
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
```

> 接下来解决第二个问题：对于两个无环单链表，如何判断其是否相交，相交时返回第一个相交的节点。
> 这个问题同样有用哈希表和不用哈希表两种方法。
> 
> 方法一：使用哈希表
> 将链表1的所有节点填入哈希表set中，对于链表2的每个节点，在哈希表中使用find()方法查找其是否在hashset中，若不在find()将返回尾后迭代器set.end()。如果链表2的每个节点都不在set中，那么就是不相交。第一个在set中的节点就是相交的第一个节点。
```c++
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
```
> 方法二：不使用哈希表。
> 需要先遍历一遍两个链表。记录每个链表的长度和最后一个节点。如果最后一个节点都不相同，那么这两个链表一定不相交。否则一定是相交的，那么就要用到两链表的长度差n来寻找第一个相交的节点。长的链表先走n步，然后与短的链表一起走，第一个相同的节点就是第一个相交的节点。（这里的相同不是指值，而是内存地址）
```c++
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
```

> 接下来解决第三个问题：对于两个有环单链表，如何判断其是否相交，相交时返回第一个相交的节点
> 
> 对于两个有环单链表，有三种拓扑结构：一是两者各自成环不相交；二是两者先相交后共享一个环；三是两者从环的不同位置入环。可以通过两个链表入环节点的位置来将这三类分为两大类：一是若两个链表入环节点相同，那么它属于第二种拓扑结构；否则它属于第一或第三种拓扑结构。
> 
> 对于第二种拓扑结构，由于其相交部分实际上是在无环部分，可以使用类似两无环链表相交问题的解法解决。不同之处在于记录长度时不再以空为截至条件而是以入环节点为截至条件。
>
> 如何区分第一和第三中拓扑结构？链表1的入环节点loop1向下走，如果遇到链表2的入环节点loop2，那么就属于第三种拓扑结构，第一个相交的节点就是入环节点(loop1和loop2都算)。如果又遇到loop1了还没遇到loop2那么就是自己成环的第一种拓扑结构，不相交。
```c++
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
``` 