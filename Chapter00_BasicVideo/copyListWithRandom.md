## 复制含有随机指针节点的链表
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/copyListWithRandom.cpp)

**题目：**
```c++
struct ListNode{
    int val;
    ListNode *next;
    ListNode *random;
    ListNode(int x):val(x),next(nullptr),random(nullptr){}
};
```
> 给定一个由ListNode节点类型组成的无环单链表的头节点head，请实现一个函数完成这个链表中所有结构的复制
> 
> 进阶：要求额外空间复杂度O(1)，时间复杂度O(N)。

> 方法一：额外空间复杂度O(N)，时间复杂度O(N)。当不要求额外空间复杂度时，也就是在笔试题目中时，可以使用哈希表unordered_map结构来实现。key是原链表中的节点，value是copy之后的节点。
> 1. 遍历第一遍，复制节点并建立哈希表map。
> 2. 遍历第二遍，搞定每个copy节点的next指针和random指针。假设有一个原节点cur，其拷贝节点curCopy，那么next指针的建立：map[cur]->next = map[cur->next]。random指针的建立：map[cur]->random = map[cur->random]。

```c++
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
```

> 方法二：额外空间复杂度O(1)，时间复杂度O(N)。这个方法不使用哈希表，而是利用拷贝节点连在原节点的后面这样的结构来省掉空间。
> 1. 遍历第一遍，复制节点并把拷贝节点连到原节点的next指针上，注意拷贝节点后面要连上下一个原节点，或者是空。
> 2. 遍历第二遍，将拷贝节点的random指针连好。注意要是原节点的random指针为空，那么就无法得到random指针的指向的空下一个节点，此时拷贝节点的random指针也应该指向空。
> 3. 遍历第三遍，将两个链表分开。注意先保存一下拷贝节点的头。

```c++
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
```