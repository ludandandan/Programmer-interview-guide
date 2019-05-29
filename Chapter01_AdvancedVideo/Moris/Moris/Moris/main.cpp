#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

class TreeNode {
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

class Moris {
public:
	void MorisPre(TreeNode *root)
	{
		if (root == nullptr) return;
		TreeNode *cur = root;
		TreeNode *mostRight = nullptr;
		//若当前节点到空就停止
		while (cur != nullptr)
		{
			mostRight = cur->left; 
			//若当前节点有左子树，那么就去它左子树的最右节点看看
			if (mostRight != nullptr)
			{
				while (mostRight->right != nullptr && mostRight->right != cur)
				{
					mostRight = mostRight->right;
				}
				//若是左子树的最右节点的右指针指向空，说明第一次来到当前节点cur
				//将此右指针指向当前节点，当前节点向左移动
				if (mostRight->right == nullptr)
				{
					cout << cur->val << ",";
					mostRight->right = cur;
					cur = cur->left;
				}
				//若是左子树的最右节点的右指针指向当前节点，说明是第二次来到当前节点cur
				//将此右指针指向空，当前节点向右移动
				else
				{
					mostRight->right = nullptr;
					cur = cur->right;
				}
			}

			//若当前节点没有左子数，那么只能来到当前节点一次（可看作第一次与第二次相同）
			//当前节点向右移动
			else
			{
				cout << cur->val << ",";
				cur = cur->right;
			}
		}
	}

	//Moris 中序遍历
	void MorisIn(TreeNode *root)
	{
		//中序遍历在第二次到达一个节点时打印
		if (root == nullptr) return;
		TreeNode *cur = root;
		TreeNode *mostRight = nullptr;
		while (cur != nullptr)
		{
			mostRight = cur->left;
			//检查当前节点的左子树是否为空
			//若左子树存在
			if (mostRight != nullptr)
			{
				//去左子树的最右节点,直到这个节点的右指针指向空或指向当前节点就停
				while (mostRight->right != nullptr && mostRight->right != cur)
				{
					mostRight = mostRight->right;
				}
				if (mostRight->right == nullptr)//第一次到达cur
				{
					mostRight->right = cur;
					cur = cur->left;
				}
				else
				{
					//第二次到达cur
					cout << cur->val << ",";
					mostRight->right = nullptr;
					cur = cur->right;
				}
			}
			//若是当前节点的左子树为空，那么只能到达当前节点一次
			//相当于第一次与第二次相同
			else
			{
				cout << cur->val << ",";
				cur = cur->right;
			}
		}
	}

	//后序遍历
	// Moris最多只能到达一个节点两次，而后序遍历需要是第三次到达这个节点。
	//对于后序遍历的规则如下：只关系可以到达两次的节点（即左子树不为空的节点）
	//只在第二次到达这个节点的时候，逆序打印
	//当遍历到一个节点发现它的左子树不是空，那么逆序打印它左子树的右边界
	//在函数退出之前逆序打印整棵树的右边界（包括根节点）
	void MorisPos(TreeNode *root)
	{
		if (root == nullptr) return;
		TreeNode *cur = root;
		TreeNode *mostRight = nullptr;
		while (cur != nullptr)
		{
			mostRight = cur->left; 
			//若左子树存在，那么就可以到达这个节点两次
			if (mostRight != nullptr)
			{
				while (mostRight->right != nullptr && mostRight->right != cur)
				{
					mostRight = mostRight->right;
				}
				//第一次到达当前节点
				if (mostRight->right == nullptr)
				{
					mostRight->right = cur;
					cur = cur->left;
				}
				//第二次到达当前节点
				else
				{
					//逆序打印当前节点左子树的右边界
					mostRight->right = nullptr;//注意必须在将最右节点的右指针指向空之后再打印左子树的右边界
					printEdge(cur->left);
					cur = cur->right;
				}
			}
			//若左子树不存在
			else
			{
				cur = cur->right;
			}
		}
		//最后逆序打印整颗树的右边界
		printEdge(root);
	}
	//逆序打印一棵树的右边界,包括根节点
	void printEdge(TreeNode *root)
	{
		TreeNode *tail = reverseEdge(root);//tail还要留着再反转回来
		TreeNode *cur = tail;
		while (cur!= nullptr)
		{
			cout << cur->val << ",";
			cur = cur->right;
		}
		reverseEdge(tail);
	}

	//反转一棵树的右边界
	TreeNode* reverseEdge(TreeNode *node)
	{
		TreeNode *pre = nullptr;
		TreeNode *next = nullptr;
		while (node != nullptr)
		{
			next = node->right;
			node->right = pre;
			pre = node;
			node = next;
		}
		return pre;
	}
};

int main()
{
	TreeNode A1(1);
	TreeNode A2(2);
	TreeNode A3(3);
	TreeNode A4(4);
	TreeNode A5(5);
	TreeNode A6(6);
	TreeNode A7(7);
	A1.left = &A2;
	A1.right = &A3;
	A2.left = &A4;
	A2.right = &A5;
	A3.left = &A6;
	A3.right = &A7;

	Moris m;
	cout << "MorisPre: ";
	m.MorisPre(&A1);
	cout << endl;
	cout << "MorisIn: ";
	m.MorisIn(&A1);
	cout << endl;
	cout << "MorisPos: ";
	m.MorisPos(&A1);
	cout << endl;
	getchar();
	return 0;
}