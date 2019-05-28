# 求最大子矩阵的大小
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/maxRectSize.cpp)

**题目：**

给定一个整型矩阵map，其中的值只有0和1两种，求其中全是1的所有矩阵区域中，最大的矩阵区域为1的数量。

例如：

[[1， 1， 1， 0]] 最大的矩阵区域有3个1，所以返回3.
```c++
[
    [1, 0, 1, 1],
    [1, 1, 1, 1],
    [1, 1, 1, 0]
]
```

最大的矩阵区域有6个1，所以返回6.

**解答：**

可以先解决输入为数组时的问题getMaxRectFromBottom，一个arr代表一个直方图，每个位置的数组代表直方图的高度，求这个直方图中面积最大的矩形的面积。

这时可以逐个计算以每个数值为高度时可达到的最大矩形面积，再从中找到最大的。以每个元素cur为高度，向左右两边扩展直到找到cur左边离cur最近的比cur小的元素的位置l和cur右边离cur最近的比cur小的元素的位置r，然后就可以确定以cur为高度的矩形的宽度（r-l-1），若是左边越界了也没找到比它还小的，那么l=-1，若右边越界了也没找到比它还小的，那么r=arr.size()。计算了宽度之后用宽度乘上高度就是矩形的面积。

解决了上面的问题后再来看原问题，对于输入为矩阵的问题，可以分别计算以每一行为底的情况下的最大矩形面积（只需生成一个直方图数组，然后调用上面的函数即可），然后从所有行中找到面积最大的就欧克了。

```c++
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
```