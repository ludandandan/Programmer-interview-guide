#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
#include <iostream>
using namespace std;

class Record {
public:
	int val;
	int times;
	Record(int x): val(x), times(1){}
};

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

int main()
{
	vector<int> arr{2,5,4,3,5,4,2,4,4,5,3};
	getVisibleNum g;
	int res = g.getVisibelNumRepeat(arr);
	cout << res << endl;
	getchar();
	return 0;
}