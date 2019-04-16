## 打印两个有序链表的公共部分
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/printCommonPart.cpp)

**题目：**
> 给定两个有序链表的头指针head1和head2，打印两个链表的公共部分。

> 这里的公共部分应该是值相等的部分，而不是两个链表相交。使用类似mergeSort中的外排的方法。若head1的val小于head2的val，那么head1向下移动；若head2的val小，那么head2向下移动；若两值相等，那么就打印，然后head1和head2都向下移动。直到两个head中的任意一个到nullptr停。

```c++
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
```