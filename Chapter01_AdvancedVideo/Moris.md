# 二叉树的Moris遍历
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/Moris.cpp)

**题目：**

给定一棵二叉树的根节点root， 完成二叉树的先序，中序和后序遍历。若二叉树的节点个数为N，则要求时间复杂度为O(N)， 额外空间复杂度O(1).

**解答：**

问题的关键在于实现额外空间复杂度O(1).二叉树的经典遍历无论是递归还是非递归方式都需要额外空间复杂度O(h)，其中h为二叉树的高度，因为二叉树只要从上到下的到达方式，要想遍历就要可以从下到上，所以需要压栈，这时就消耗了空间。

Moris遍历充分利用了在底层的nullptr节点来实现从下到上。

## Moris遍历的通用规则：

假设来到的当前节点为cur

1. 若cur没有左孩子，那么cur向右移动，cur = cur->right
2. 若cur有左孩子，找到cur左子树上最右的节点，记为mostRight
   1.  若mostRight的右指针指向空，那么就让他指向当前节点cur，然后当前节点向左移动，cur=cur->left
   2.  若mostRight的右指针指向当前节点cur，那么就让它指向空，然后当前节点向右移动cur=cur->right
   
Moris遍历最多来到一个节点两次。对于有左子树的节点，那么就会来到一个节点两次；对于没有左子树的节点，那么就会来到一个节点一次。


经典二叉树遍历的递归方法会来到一个节点三次。若在第一次来到这个节点时打印就是先序遍历，若是在第二次来到这个节点时打印就是中序遍历，若是在第三次来到这个节点时打印就是后序遍历。

那么对于Moris遍历如何区别是第几次来到这个节点的呢？
1. 对于有左子树的cur, 看mostRight的右指针，若它是指向空的，那么这是第一次遍历到cur，若它是指向cur的，那么这就是第二次遍历到cur，（并且cur的左子树上的所有节点都已经遍历完了）。
2. 对于没有左子树的cur，那么可以认为第一次和第二次是一起遍历到cur的。也就是遍历到cur时可以看做是第一次也可以看做是第二次。
   
那么我们就通过将Print放在合适的位置实现先序和中序遍历。可是对于后序遍历，是需要第三次到达某个节点时打印，它的规则如下：
1. 后序遍历只关系可以两次到达的节点（即有左子树的节点）。
2. 到第二次到达这个节点时，**必须先将mostRight的右指针指向空**，然后逆序打印cur的左子树的右边界。
3. 在函数退出之前，逆序打印整棵树的右边界（包括根节点）。
   
如何在额外空间复杂度为O(1)要求下逆序打印一棵树的右边界。

    类似链表反转的方式，先把右边界反转，然后遍历打印，然后再反转回来。

    先让头节点的右指针指向空，然后再让后面的节点的右指针指向前面的节点。

```c++
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
```

