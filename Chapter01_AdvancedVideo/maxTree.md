# 构造数组的MaxTree
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/maxTree.cpp)

**题目：**

定义二叉树节点如下：
```c++
class Node{
public:
    int value;
    Node left;
    Node right;
    Node(int data): value(data), left(nullptr), right(nullptr){}
};
```

一个数组的MaxTree定义如下：

1. 数组必须没有重复元素。
2. MaxTree是一棵二叉树，数组的每一个值对应一个二叉树节点。
3. 包括MaxTree树在内且在其中的每一棵子树上，值最大的节点都是树的头。
4. 没有重复元素的数组arr，写出生成这个数组的MaxTree的函数，要求如果数组长度为N，时间复杂度为O(N)，空间复杂度O(N)。


**方法一：** 使用大根堆来实现。

一个数组的MaxTree有若干结构，其中大根堆构成的二叉树一定是满足条件的一种。大根堆是一棵完全二叉树，任何一棵子树的最大值都是其头部。


**方法而：** 使用单调栈来实现。

首先需要一个哈希表把所有的数字建一个节点存起来，到时候根据索引取出来连接

单调栈从底到顶从大到小。
1. 若是cur的左右两边都没有比它大的，那么cur就是root。注意，Node在定义时必须要初始化，但是若是初始化为Nullptr那么就只能通过赋值改变了，Nullptr是没有val，left和right的
2. 若是cur的左右两边都有比它大的，那么就取其中较小的那个，让cur挂在它后面，至于是放在left还是right，可以优先放在left，若left上有了那么再放在right上。
3. 若是cur 左右两边只有一边有比它大的，那么就直接将cur 挂在它后面。

```c++
class TreeNode {
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
void inorder(TreeNode *root);
void preorder(TreeNode *root);
//实现数组的maxTree。由数组构建一棵二叉树，它的头节点是整个树（子树）中值最大的



class maxTree {
public:
	//使用大根堆来实现，因为大根堆就是一个完全二叉树，并且它的任何一棵子树的最大值就是它的头部
	TreeNode * getMaxTree(vector<int> arr)
	{
		//优先级队列大根堆
		priority_queue<int, vector<int>, less<int>> heap;
		for (int i = 0; i < arr.size(); i++)
		{
			heap.push(arr[i]);
		}
		//把大根堆建为二叉树
		TreeNode *root = new TreeNode(heap.top()); //根
		heap.pop();
		stack<TreeNode *> s;
		s.push(root);
		while (!heap.empty() && !s.empty())
		{
			TreeNode *head = s.top();
			s.pop();
			//先连左孩子再连右孩子，
			//然后压栈，先压右孩子，后压左孩子

			if (!heap.empty())
			{
				TreeNode *left = new TreeNode(heap.top());
				head->left = left;
				heap.pop();
			}
			if (!heap.empty())
			{
				TreeNode *right = new TreeNode(heap.top());
				head->right = right;
				heap.pop();
			}
;
			if(head->right != nullptr) s.push(head->right);
			if (head->left != nullptr) s.push(head->left);
		}
		return root;
	}
	

	//使用单点栈构造maxTree，
	//若一个值它左边离它最近的为Null，右边离它最近的为Null，那么这个值就是头节点
	//若一个值它左右都有值，那么就选择小的，挂在它后面
	//若一个值它左右只有一边有值，那么就直接挂在它后面

	TreeNode* getMaxTree2(vector<int> arr)
	{
		//可能需要一个哈希表
		unordered_map<int, TreeNode *> map;
		//先把所有的数建好Node放到哈希表里面
		for (int i = 0; i < arr.size(); i++)
		{
			TreeNode *cur = new TreeNode(arr[i]);
			map.insert({ i, cur });//无重复数字
		}
		//建一个栈，从底到顶从大到小的
		stack<int> s;//栈里面放的是位置信息
		TreeNode *root = nullptr;
		for (int i = 0; i < arr.size(); i++)
		{
			while(!s.empty() && arr[s.top()] < arr[i])
			{
				int index = s.top();
				s.pop();
				int rightMore = arr[i];
				int leftMore = s.empty() ? INT_MAX : arr[s.top()];
				int father_index = rightMore < leftMore ? i : s.top();
				if (map[father_index]->left == nullptr) map[father_index]->left = map[index];
				else map[father_index]->right = map[index];
			}
			s.push(i);
		}
		//对于右边比它最大的没有
		while (!s.empty())
		{
			int index = s.top();
			s.pop();
			int rightMore = INT_MAX;
			int leftMore = s.empty() ? INT_MAX : s.top();
			if (leftMore == INT_MAX) root = map[index];
			else
			{
				int father_index = s.top();
				if (map[father_index]->left == nullptr) map[father_index]->left = map[index];
				else map[father_index]->right = map[index];
			}
		}
		return root;
	}
};
```