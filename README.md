# 《程序员面试指南》
使用C++实现左老师书及视频中出现的题目代码
## 目录
- [基础班题目](#基础班题目)
- [栈和队列](#栈和队列)
- [链表问题](#链表问题)

# 基础班题目
| ID | Title                                  |           C++             |      难度       |          备注               |
|:--:|:--------------------------------------:|:-------------------------:|:---------------|:---------------------------:|
|0001| 找出B中不属于A的数并打印|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/findBNotBelongToA.md)|:star:|三种方法：遍历，二分搜索，排序+外排|
|0002|冒泡排序|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/BubbleSort.md)|:star:|排序，稳定|
|0003|选择排序|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/SelectionSort.md)|:star:|排序，不稳定|
|0004|插入排序|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/InsertSort.md)|:star:|排序，稳定|
|0005|递归求数组最大值|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/Recursive_getMax.md)|:star:|递归及递归复杂度分析，master公式|
|0006|归并排序|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/MergeSort.md)|:star:|排序，递归，分治，稳定|
|0007|求数组的小和|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/smallSum.md)|:star: :star: :star:|归并排序，递归，分治|
|0008|求数组的逆序对|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/print_ReverseOrderPair.md)|:star: :star: :star:|归并排序，递归，类似小和|
|0009|partition|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/partition.md)|:star:|思想用于快排|
|0010|荷兰国旗问题|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/NetherlandsFlag.md)|:star:|思想用于快排|
|0011|随机快排|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/QuickSort.md)|:star: :star:|排序，递归，partition，不稳定|
|0012|堆排序|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/HeapSort.md)|:star: :star:|排序，大根堆，不稳定|
|0013|随时找到数据流中的中位数|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/MedianHolder.md)|:star: :star: :star: :star:|大根堆，小根堆|
|0014|比较器|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/comparator.md)|:star: :star:|排序的稳定性|
|0015|用数组实现大小固定的队列和栈|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/arrayToStackQueue.md)|:star: :star:|栈，队列|
|0016|设计一个有getMin功能的栈|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/getMin.md)|:star:|栈|
|0017|数组排序之后相邻两数的最大差值|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/maxGap.md)|:star:|桶排序|
|0018|用队列结构实现栈&用栈结构实现队列|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/stackAndQueueConvert.md)|:star: :star:|栈，队列|
|0019|猫狗队列|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/DogCatQueue.md)|:star:|队列，类|
|0020|转圈打印矩阵|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/spiralOrderPrint.md)|:star:|矩阵|
|0021|将正方形矩阵顺时针旋转90度|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/rotateMatrix.md)|:star:|矩阵|
|0022|之字打印矩阵|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/printMatrixZigZag.md)|:star:|矩阵|
|0023|在行和列都排好序的矩阵中找数|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isContainsInMatrix.md)|:star:|矩阵|
|0024|打印两个有序链表的公共部分|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/printCommonPart.md)|:star:|链表|
|0025|判断链表是否为回文结构|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/ListNodeIsPalindrome.md)|:star:|链表|
|0026|将单链表按某值划分为左边小，中间相等，右边大的形式|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/ListPartition.md)|:star: :star:|链表，荷兰国旗|
|0027|复制含有随机指针节点的链表|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/copyListWithRandom.md)|:star: :star:|链表，哈希表|
|0028|两个链表相交的一系列问题|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/FindFirstIntersectNode.md)|:star: :star: :star: :star:|链表，哈希表|
|0029|二叉树的先序，中序和后序遍历|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/PreInPosTraversing.md)|:star: :star: |二叉树|
|0030|带父节点的二叉树中找到一个节点的后继节点，前驱节点|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/getSuccessorNode.md)|:star: :star: |二叉树|
|0031|二叉树的序列化和反序列化|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/serial.md)|:star: |二叉树，字符串分割函数，stoi，to_string|
|0032|判断是否为平衡二叉树|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isBalanceTree.md)|:star: |二叉树，平衡性|
|0033|判断是否为搜索二叉树|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isBST.md)|:star: |搜索二叉树|
|0034|判断是否为完全二叉树|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isCBT.md)|:star: |完全二叉树|
|0035|求完全二叉树的节点个数|[查看题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/nodeNum.md)|:star: |完全二叉树，递归|
# 栈和队列

| ID | Title                                  |           C++             |      难度       |          备注               |
|:--:|:--------------------------------------:|:-------------------------:|:---------------:|:---------------------------:|
|1001| 设计一个有getMin功能的栈|[查看题解]() |:star:|栈|

<br>[:top:回到顶部](#程序员面试指南)

# 链表问题