#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

class maxRect {
public:
	int maxRectFromBottom(vector<int> arr)
	{
		//求这个数组arr构成的直方图中面积最大的矩形的面积
		//以每一列为高度向两边扩，到离的最近的比这个高度小的数就停止，
		//记录位置信息用于计算矩形的面积
		stack<int> s; //从底到顶从小到大
		int maxArea = INT_MIN;
		for (int i = 0; i < arr.size(); i++)
		{
			while (!s.empty() && arr[s.top()] > arr[i])
			{
				int index = s.top();
				s.pop();
				//计算以arr[index]为高的矩形的最大面积
				int r = i;
				int l = s.empty() ? -1 : s.top();
				int area = arr[index] * (r - l - 1);
				maxArea = max(area, maxArea);
			}
			s.push(i);
		}
		while (!s.empty())
		{
			int index = s.top();
			s.pop();
			int r = arr.size();
			int l = s.empty()? -1:s.top();
			int area = arr[index] * (r - l - 1);
			maxArea = max(area, maxArea);
		}
		return maxArea;
	}

	int maxRect2(vector<vector<int>> m)
	{
		//求最大子矩阵的面积
		//分别求出以每一行为底时的最大矩形面积，然后再求这里面的最大值
		if (m.empty() || m[0].empty()) return 0;
		int maxArea = INT_MIN;
		int r = m.size();
		int c = m[0].size();
		vector<int> height(c, 0);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				height[j] = m[i][j] == 0 ? 0 : height[j] + 1;
			}
			maxArea = max(maxArea, maxRectFromBottom(height));
		}
		return maxArea;
	}
};

int main()
{
	vector<int> arr{4,3,2,5,6};
	maxRect m;
	int maxArea = m.maxRectFromBottom(arr);
	cout << maxArea << endl;
	vector<vector<int>> ma{
		{1, 0, 1, 1},
		{1, 1, 1, 1},
		{1, 1, 1, 0}
	};
	int maxArea2 = m.maxRect2(ma);
	cout << maxArea2 << endl;
	getchar();
	return 0;
}