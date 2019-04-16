## 链表的荷兰国旗问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/ListPartition.cpp)

**题目：**
> 给定一个单链表的头节点head，节点的值类型为整型，再给定一个整数num，实现一个调整链表的函数，将链表调整为左部分都是值小于num的节点，中间部分都是值等于num的节点，右部分都是值大于num的节点。
> 
> 进阶：在原问题的基础上添加两个要求：
> 1. 在左中右三个部分放入内部也做顺序要求，要求每部分里的节点从左到右的顺序与原链表中节点的先后次序一致。
> 2. 如果链表长度为N，要求时间复杂度O(N)，空间复杂度O(1)。

> 对于初级的要求，可以使用一个vector数组，数组中保存ListNode*类型，将链表中的每个节点都放都vector中，然后应用荷兰国旗的解法将这些节点按照值分为小于等于和大于三部分。然后遍历一遍vector，将所有节点连接起来，不要忘记最后的节点的next指向空。
```c++
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
```

> 对于进阶的要求，首先荷兰国旗不能做到稳定，不满足进阶的第一个要求，然后初级中的方法使用了一个vector，额外空间复杂度为O(1)。为了能达到进阶的要求，需要准备三组ListNode*类型的变量: less和lessEnd用于记录小于区域，equal和equalEnd用于记录等于区域，more和moreEnd用于记录大于区域。
> 
> 先遍历一遍链表，找到第一个值小于num的节点，让less等于这个节点，找到第一个值等于num的节点，让equal等于这个节点，找到第一个值大于num的节点，让more等于这个节点。
> 然后再遍历一遍链表，若发现值小于num的节点，看看它是不是less，如果不是就用lessEnd挂在less后面，同时lessEnd向下移动，对于等于区域和大于区域也是一样。
> 
> 最后将这三个区域连接起来。小于区域的尾巴lessEnd连等于区域的头equal，等于区域的尾巴连大于区域的头，特别注意当有的区域中没有节点的情况。如果一个区域的尾巴为空那么这个区域一定为空。如果小于区域的尾巴不是空的话，就把小于区域的尾巴连到等于区域的头上，然后检查等于区域的尾巴是不是空，如果是空的话就让等于区域的尾巴等于小于区域的尾巴，以后拿等于区域的尾巴去连大于区域的头时相当于拿小于区域的尾巴连大于区域的头，因为等于区域没有值。然后判断等于区域的尾巴是不是空的（如果它是空的就说明小于等于区域都没数），如果不是空的就拿等于区域的尾巴去连大于区域的头。然后判断大于区域的尾巴是不是空的，如果不是就让它连向空（因为要保证链表的最后的next指向空）。返回的时候看从小于开始，看哪个的头不是空就返回哪个。总之就是连的时候依次看三个区域的尾巴是不是空，不是空进行相应的操作。返回看头是不是空。
```c++
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

```