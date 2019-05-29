# 可见山峰的数量
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/getVisibleNum.cpp)

**题目：**
一个不含有负数的数组可以代表一圈环形山，每个位置的值代表山的高度。比如，{3,1,2,4,5},{4,5,3,1,2},{1,2,4,5,3}都代表同样的环形山。3->1->2->4->5->3叫做next方向（逆时针），3->5->4->2->1->3叫做last方向（顺时针）。

山峰A和山峰B能够相互看见的条件为
1. 若A和B为同一座山峰，认为不能相互看见。
2. 若A和B是不同的山峰，并且在环中相邻，认为可以相互看见
3. 若A和B是不同的山峰，并且在环中不相邻，假设两座山高度的最小值为min。若A通过next方向到B的途中没有高度比min大的山峰，或者A通过last方向到B的途中没有高度比min大的山峰，认为A和B可以相互看见。

给定一个不含有负数且没有重复值的数组arr，返回有多少对山峰能够相互看见。

**进阶问题：**

给定一个不含有负数但可能含有重复值的数组arr，返回有多少对山峰能够相互看见

**要求：**

如果arr长度为N，没有重复值的情况下时间复杂度达到O(1)；可能有重复值的情况下时间复杂度O(N)

**解答：**

## 对于原问题：

统计个数的时候按照这样的规则：小的数去找大的数。
比如数数组中位置i的数arr[i]，那么分别向左向右找到刚比它大的数x和y（比arr[i]小的就忽略，因为我们规定是小的找大的，而不需要大的找小的）

为了方便，我们先找到数组中最大的数h1和第二大的数h2，那么其他的数arr[i]都会在顺时针和逆时针方向找到刚刚比它自己大的数，假设数组中数有n个，那么除去最大和次大还剩n-2个数，这些数每个都会找到2对山峰，故有\(n-2\)\*2对山峰，再加上h1和h2构成的山峰对，那么就有\(n-2\)\*2+1对，也就是2*n-3对。

1. 若n=1,那么就是0对
2. 若n=2,那么就是1对
3. 若n=3，那么就是2*n-3对
   
直接根据n就可以得到答案，时间复杂度为O(1)

## 对于进阶问题：

还是用小的数去找大的，还是要找到最大的数。

因为要找到左右两边离它最近的比它大的数，那么可以使用单调栈来实现。

先找到一个最大的数（就是若是有多个最大的那么就取一个），以这个最大元素所在位置开始进行遍历。这样就会先把这个最大元素压栈。单调栈从栈底到栈顶是从大到小的。这样这个元素就会一直在栈底，以保证以后的元素在一个方向上必然有一个比它大的了（在这个元素底下的元素），那么另外一个方向上的就要看是谁让它弹出来的了。同时因为是环形的，就算遍历的时候没有因为谁而出栈，另一个方向上也可能有比它大的。

注意，在栈中压入的是一个数据结构（val, times）表示值为val的数字有times个。

对于在数组遍历过程中出栈的元素，若times==1，那么它对应的山峰对数就是2. 若times=k，那么这k个元素内部可以两两相互看见，那就有$C_{k}^{2}$，同时他们两个方向也都可以找到比他们大的元素，就又有2*k，所以这种就会有山峰对数为$C_{k}^{2}+2*k$。

对于遍历完之后还留在栈里的元素，若栈里留下的记录>=3条，那么对于从底起第3条记录往上的计算方法还是$C_{k}^{2}+2*k$。因为下面的两条记录可以保证上面的元素在左右两个方向上有比它大的，也就可以产生两对山峰2*k,而他们内部两两互相可见。

对于倒数第2条记录，那么就要看最后一条记录的times是多少，若是times>=2，那么倒数第二条记录可以产生的山峰对数就是$C_{k}^{2}+2*k$，若times=1那么就是$C_{k}^{2}+1*k$.

对于最后一条记录，它只能内部看见（有小找大）那么就要看它自己的times是多少，若times=1， 那么就是0对，若是times>=2，那么就是$C_{k}^{2}$

所以需要一个计算$C_{k}^{2}$的函数，还要构建一个新的结构（val, times）

```c++
class getVisibleNum {
public:
	//对于没有重复数字的数组，可以在O(1)时间内得到可见山峰对的数量
	int getVisibleNumNoRepeat(vector<int> arr)
	{
		if (arr.empty() || arr.size() == 1) return 0;
		if (arr.size() == 2) return 1;
		int n = arr.size();
		return 2 * n - 3;
	}
	//计算C_{k}^2的函数
	//若是k=1那么返回0，
	int getInternalSum(int k)
	{
		return k == 1 ? 0 : (k*(k - 1) / 2);
	}
	//对于可能有重复数字的数组，在O(N)时间内得到可见山峰对的数量
	int getVisibelNumRepeat(vector<int> arr)
	{
		if (arr.empty() || arr.size() == 1) return 0;
		if (arr.size() == 2) return 1;
		stack<Record> s;//单调栈，从底到顶从大到小
		int res = 0;//记录山峰对的数量
		//先找到最大值所在的位置，以这个位置开始进行遍历
		int max_index;
		int maxval = INT_MIN;
		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i] > maxval)
			{
				maxval = arr[i];
				max_index = i;
			}
		}
		//从max_index开始遍历
		int i = max_index;
		int c = 0;
		while (c == 0 || i != max_index)
		{
			c++;
			//若是遇到比当前栈顶大的，栈顶元素弹出并进行结算
			while (!s.empty() && s.top().val < arr[i])
			{
				res += getInternalSum(s.top().times) + 2 * s.top().times;
				s.pop();
			}
			//若是遇到相等的那么就让k++
			if (!s.empty() && s.top().val == arr[i]) ++s.top().times;
			else
			{
				Record r(arr[i]);
				s.push(r);
			}
			i++;
			if (i == arr.size()) i = 0;
		}

		//对于遍历完了以后还在栈里的
		while (s.size() > 2)
		{
			//对于倒数第3，4...的处理方法与上面一样
			res += getInternalSum(s.top().times) + 2 * s.top().times;
			s.pop();
		}

		//对于倒数第2个,需要看倒数第1的times
		if (s.size() == 2)
		{
			int times2 = s.top().times;
			s.pop();
			if (s.top().times >= 2) res += getInternalSum(times2) + 2 * times2;
			else res += getInternalSum(times2) + s.top().times;
		}
		if (s.size() == 1)
		{
			res += getInternalSum(s.top().times);
			s.pop();
		}
		return res;
	}
};
```