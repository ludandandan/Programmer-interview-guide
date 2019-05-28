#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;
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

int main()
{
	vector<int> arr{3,2,4,1,0,5};
	maxTree m;
	TreeNode *root = m.getMaxTree(arr);
	preorder(root);
	cout << endl;
	inorder(root);
	
	cout << endl;
	TreeNode *root1 = m.getMaxTree2(arr);
	preorder(root1);
	cout << endl;
	inorder(root1);
	getchar();

	return 0;
}

//中序遍历
void inorder(TreeNode *root)
{
	if (root == nullptr) return;
	
	inorder(root->left);
	cout << root->val << ",";
	inorder(root->right);
}
void preorder(TreeNode *root)
{
	if (root == nullptr) return;
	cout << root->val << ",";
	preorder(root->left);
	preorder(root->right);
}