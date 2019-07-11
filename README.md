# 《程序员面试指南》
使用C++实现左老师书及视频中出现的题目代码
## 目录
- [基础班题目](#基础班题目)
- [进阶班题目](#进阶班题目)
- [栈和队列](#栈和队列)
- [链表问题](#链表问题)
- [字符串问题](#字符串问题)

# 基础班题目
| ID | Title                                  |           C++             |      难度       |          备注               |
|:--:|:--------------------------------------:|:-------------------------:|:---------------|:---------------------------:|
|0001| 找出B中不属于A的数并打印|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/findBNotBelongToA.md)|:star:|三种方法：遍历，二分搜索，排序+外排|
|0002|冒泡排序|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/BubbleSort.md)|:star:|排序，稳定|
|0003|选择排序|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/SelectionSort.md)|:star:|排序，不稳定|
|0004|插入排序|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/InsertSort.md)|:star:|排序，稳定|
|0005|递归求数组最大值|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/Recursive_getMax.md)|:star:|递归及递归复杂度分析，master公式|
|0006|归并排序|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/MergeSort.md)|:star:|排序，递归，分治，稳定|
|0007|求数组的小和|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/smallSum.md)|:star: :star: :star:|归并排序，递归，分治|
|0008|求数组的逆序对|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/print_ReverseOrderPair.md)|:star: :star: :star:|归并排序，递归，类似小和|
|0009|partition|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/partition.md)|:star:|思想用于快排|
|0010|荷兰国旗问题|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/NetherlandsFlag.md)|:star:|思想用于快排|
|0011|随机快排|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/QuickSort.md)|:star: :star:|排序，递归，partition，不稳定|
|0012|堆排序|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/HeapSort.md)|:star: :star:|排序，大根堆，不稳定|
|0013|随时找到数据流中的中位数|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/MedianHolder.md)|:star: :star: :star: :star:|大根堆，小根堆|
|0014|比较器|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/comparator.md)|:star: :star:|排序的稳定性|
|0015|用数组实现大小固定的队列和栈|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/arrayToStackQueue.md)|:star: :star:|栈，队列|
|0016|设计一个有getMin功能的栈|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/getMin.md)|:star:|栈|
|0017|数组排序之后相邻两数的最大差值|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/maxGap.md)|:star:|桶排序|
|0018|用队列结构实现栈&用栈结构实现队列|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/stackAndQueueConvert.md)|:star: :star:|栈，队列|
|0019|猫狗队列|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/DogCatQueue.md)|:star:|队列，类|
|0020|转圈打印矩阵|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/spiralOrderPrint.md)|:star:|矩阵|
|0021|将正方形矩阵顺时针旋转90度|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/rotateMatrix.md)|:star:|矩阵|
|0022|之字打印矩阵|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/printMatrixZigZag.md)|:star:|矩阵|
|0023|在行和列都排好序的矩阵中找数|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isContainsInMatrix.md)|:star:|矩阵|
|0024|打印两个有序链表的公共部分|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/printCommonPart.md)|:star:|链表|
|0025|判断链表是否为回文结构|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/ListNodeIsPalindrome.md)|:star:|链表|
|0026|将单链表按某值划分为左边小，中间相等，右边大的形式|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/ListPartition.md)|:star: :star:|链表，荷兰国旗|
|0027|复制含有随机指针节点的链表|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/copyListWithRandom.md)|:star: :star:|链表，哈希表|
|0028|两个链表相交的一系列问题|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/FindFirstIntersectNode.md)|:star: :star: :star: :star:|链表，哈希表|
|0029|二叉树的先序，中序和后序遍历|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/PreInPosTraversing.md)|:star: :star: |二叉树|
|0030|带父节点的二叉树中找到一个节点的后继节点，前驱节点|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/getSuccessorNode.md)|:star: :star: |二叉树|
|0031|二叉树的序列化和反序列化|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/serial.md)|:star: |二叉树，字符串分割函数，stoi，to_string|
|0032|判断是否为平衡二叉树|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isBalanceTree.md)|:star: |二叉树，平衡性|
|0033|判断是否为搜索二叉树|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isBST.md)|:star: |搜索二叉树|
|0034|判断是否为完全二叉树|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isCBT.md)|:star: |完全二叉树|
|0035|求完全二叉树的节点个数|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/nodeNum.md)|:star: :star:|完全二叉树，递归|
|0036|设计RandomPool结构|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/RandomPool.md)|:star: :star:|哈希表，类|
|0037|实现并查集结构|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/unionFind.md)|:star: :star:|哈希表，类|
|0038|岛问题|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/Islands.md)|:star: :star:|并查集，DFS|
|0039|实现前缀树结构|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/TrieTree.md)|:star: :star:|前缀树|
|0040|拼接所有字符串产生字典序最小的字符串|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/LowestLexicography.md)|:star: :star:|字符串比较，比较器，贪心|
|0041|分金条问题|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/LessMoney.md)|:star: :star:|哈夫曼编码，最小代价，小根堆，贪心|
|0042|IPO问题|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/IPO.md)|:star: :star:|贪心，大根堆，小根堆，比较器|
|0043|安排会议室宣讲问题|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/BestArrange.md)|:star: :star:|贪心，比较器|
|0044|n的阶乘|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/Factorial.md)|:star:|暴力递归|
|0045|汉诺塔问题|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/hanoi.md)|:star: :star: :star:|递归|
|0046|打印字符串的全部子序列|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/printAllSubsquences.md)|:star: :star:|递归|
|0047|打印字符串的全排列|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/printAllPermutations.md)|:star: :star:|递归|
|0048|:cow:母牛问题|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/cow.md)|:star:|递归|
|0049|最小路径和|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/minPath.md)|:star: :star:|递归，动态规划|
|0050|数组中任意个数的累加能否得到aim|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/isSumAim.md)|:star: :star:|递归，动态规划|

# 进阶班题目

| ID | Title                                  |           C++             |      难度       |          备注               |
|:--:|:--------------------------------------:|:-------------------------:|:---------------:|:---------------------------:|
|0001|生成窗口最大值数组|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/getWindowsMaxArr.md)|:star: :star:|窗口|
|0002|最大值减去最小值小于或等于num的子数组数量|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/getSubarrayNum.md)|:star: :star: :star:|窗口|
|0003|找到无序数组中最小的k个数|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/bfprt.md)|:star: :star: :star: :star:|bfprt|
|0004|单调栈结构|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/getNearLess.md)|:star: :star:|单调栈|
|0005|maxTree|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/maxTree.md)|:star: :star:|单调栈，大根堆，哈希表|
|0006|求最大子矩阵的大小|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/maxRectSize.md)|:star: :star: :star:|单调栈|
|0007|可见的山峰对数量|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/getVisibleNum.md)|:star: :star: :star: :star:|单调栈|
|0008|二叉树的Moris遍历|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/Moris.md)|:star: :star: :star: :star:|二叉树，遍历|
|0009|大楼轮廓问题|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/TreeMap.md)|:star: :star: :star: :star:|平衡搜索二叉树，map，比较器|
|0010|未排序数值中累加和为给定值的最长子数组系列问题|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/aimMaxLength.md)|:star: :star:|map，子数组|
|0011|子数组异或和为0的最多划分|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/mostEOR.md)|:star: :star: :star:|map，子数组|
|0012|求最大搜索二叉树的大小|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/maxBST.md)|:star: :star: :star:|树形dp|
|0013|字符串包含问题|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/strStrKMP.md)|:star: :star: :star: :star:|KMP算法|
|0014|扩展字符串使包含两个原始串|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/extendStr.md)|:star: :star:|KMP算法, next数组|
|0015|判断t1树中是否有与t2树拓扑结构完全相同的子树（子树包含问题）|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/isSubTree.md)|:star: :star: :star:|KMP算法, next数组, find|












# 栈和队列

| ID | Title                                  |           C++             |      难度       |          备注               |
|:--:|:--------------------------------------:|:-------------------------:|:---------------:|:---------------------------:|
|1012| 将单链表的每K个节点之间逆序|[查看题解]() |:star: :star|栈，链表|

<br>[:top:回到顶部](#程序员面试指南)

# 链表问题


| ID | Title                                  |           C++             |      难度       |          备注               |
|:--:|:--------------------------------------:|:-------------------------:|:---------------:|:---------------------------:|
|1001| 设计一个有getMin功能的栈|[查看题解]() |:star:|栈|

<br>[:top:回到顶部](#程序员面试指南)

# 字符串问题
| ID | Title                                  |           C++             |      难度       |          备注               |
|:--:|:--------------------------------------:|:-------------------------:|:---------------:|:---------------------------:|
|0001|判断两个字符串是否为变形词|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter06_String/01isDeformation.md)|:star:|哈希表|
|0007|字符串的调整与替换|[题解](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter06_String/07replace.md)|:star:|逆序复制，空字符|


<br>[:top:回到顶部](#程序员面试指南)