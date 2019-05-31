# 大楼轮廓问题
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/TreeMap.cpp)

**题目：**

给定一个N*3的矩阵matrix，对于每一个长度为3的小数组arr，都表示一个大楼的三个数据。arr[0]表示大楼的左边界，arr[1]表示大楼的右边界，arr[2]表示大楼的高度（一定大于0）。每座大楼的地基都在X轴上，大楼之间可能会有重叠，请返回整体的轮廓线数组。

**举例：**
```c++
matrix = {{2,5,6},{1,7,4},{4,6,7},{3,6,5},{10,13,2},{9,11,3},{12,14,4},{10,12,5}}

//返回的轮廓线数组如下：
{{1,2,4},{2,4,6},{4,6,7},{6,7,4},{9,10,3},{10,12,5},{12,14,4}}
```

**要求：**

时间复杂度O(NlogN)

**解答：**

## 平衡搜索二叉树：

具有某种平衡性的搜索二叉树。搜索二叉树，左子树上的节点值都比头节点小，右子树上的节点值都比头节点大。具有平衡性是为了保证增删改查的时间复杂度是O(logN)。

在c++中的map就是使用红黑树实现的，这种map中的key是按照一定的顺序组织的(key从小到大)，所有若要取出key最小的数：

```c++
#include <key>
key<int, string> m;
m.insert({1,"111"});
m.insert({4,"444"});
m.insert({2, "222"});

cout << m.begin()->first << endl; //这样就会打印出最小的key 1
cout << (--m.end())->first << endl; //这样就会打印出最大的key 4
```


大楼轮廓的出现一定是在当前最大高度发生变化的情况下。要找一个结构可以记录随时更新所有的高度信息，同时可以很快的得到其中的最大高度，以便检查最大高度有无发生变化，这里就可以用到平衡搜索二叉树，因为他们的key是按照顺序组织的,maxkey可以在O(logN)时间找到。

建一个Map，里面的key表示高度，value表示当前的条数（若有一个key上去那么value++,若有一个key下来，那么value--,若value变为0了，那么就把这个key连同value一起删掉，表示key高度现在没有了）

解答步骤如下：

1. 先把大楼信息进行拆分：把[左边界，右边界，高度]拆分为两个信息[左边界，高度，上]和[右边界，高度，下]
```c++
//原信息：
{{1,6,4},{2,4,3},{5,8,5},{7,10,3}}
//拆分后信息
{
    {1,4,up}，{6,4,down},
    {2,3,up}, {4,3,down},
    {5,5,up}, {8,5,down},
    {7,3,up}, {10,3,down},
}
```

构造一个结构，把拆分后的大楼信息都改为Node类型，放到一个vector<Node>里面
```c++
//定义一个节点，表示位置，高度，是上还是下
class Node {
public:
	int pos;
	int h;
	bool isUp;
	Node(int x, int y, bool z):pos(x),h(y),isUp(z){}
};
```
2. 按照边界（位置）信息进行排序，从小到大。
```c++
{
    {1,4,up},{2,3,up},{4,3,down},{5,5,up},{6,4,down},{7,3,up},{8,5,down},{10,3,down}
}
```
需要定义一个比较器，直接用sort进行排序。若是位置不同，按从到大；若位置相同，那再看isUp，先上后下，若是这个也一样，那么再看高度，先高后低
```c++
//定义Node的比较策略，按照位置排序，从小到大，若位置相同，那么把先上的放在前面
bool comparator(Node *o1, Node *o2)
{
	if (o1->pos != o2->pos)
		return o1->pos < o2->pos;
	if (o1->isUp != o2->isUp)//从小到大
		return o1->isUp;//先上后下
	if (o1->h != o2->h)
		return o1->h > o2->h;//从大到小
}
```


3. 需要两个map结构，一个mapHeightTimes用于及时更新，得到当前最大的高度；令一个mapPosMaxHeight用于记录，记录每个位置的最大高度用于后面生成结果信息。
   1. 第一个mapHeightTimes的key是高度，value是这个高度的条数。依次处理vector<Node>里面的信息，若是isUp上的，那么就要添加高度，先检查这个高度之前出现过吗，若没有那就插入，若有将value++；若是下的，那么就要去除高度，看看这个高度当前是的value是1吗，是就直接移除erase，若不是value--。
   2. 在依次处理vector<Node>里面信息时，同时将现在的Node的位置和目前的最大高度记录在mapPosMaxHeight, 这个map的key是位置，value是这个位置的最大高度。
4. 根据mapPosMaxHeight生成最后的结果信息。依次处理mapPosMaxHeight中的各个元素node，key是位置,value是最大高度。先定义两个之前的开始位置start=0, 高度height=0
   1. 若现在node的高度与之前的高度height不一致，说明最大高度发生了变化，要产生轮廓了。
      1. 若start当前等于0，那么就没办法生成一个结果信息，而只能说明先从node的位置开始，高度为node现在的高度，到哪里截至不确定，将start更新为node的位置，将height更新为node当前的高度。
      2. 若start不为0，说明从start开始高度为height的大楼轮廓从这里收尾了，生成结果信息，保存在结果里。同时更新start和height
   2. 若是node 的高度与height的高度一致，那么就不用管了
   


> 注意： map插入不能覆盖，需要先检查是否在Map里，若在就修改，若不在就插入



```c++
//定义一个节点，表示位置，高度，是上还是下
class Node {
public:
	int pos;
	int h;
	bool isUp;
	Node(int x, int y, bool z) :pos(x), h(y), isUp(z) {}
};
//定义Node的比较策略，按照位置排序，从小到大，若位置相同，那么把先上的放在前面
bool comparator(Node *o1, Node *o2)
{
	if (o1->pos != o2->pos)
		return o1->pos <= o2->pos;
	if (o1->isUp != o2->isUp)//从小到大
		return o1->isUp;//先上后下
	if (o1->h != o2->h)
		return o1->h >= o2->h;//从大到小
	return false;
}
class building {
public:
	vector<vector<int>> buildingOutline(vector<vector<int>> matrix)
	{
		//输入的matrix按照[左边界，右边界，高度]组织
		vector<vector<int>> res;
		if (matrix.empty() || matrix[0].empty()) return res;
		//先对信息进行拆分，构成Node,并把这些Node放到vector里
		int n = matrix.size();//一共有多少栋大楼
							  //那么就会有2*n条Node信息
		vector<Node*> nodes(2 * n);
		for (int i = 0; i < n; i++)
		{
			nodes[2 * i] = new Node(matrix[i][0], matrix[i][2], true);//上
			nodes[2 * i + 1] = new Node(matrix[i][1], matrix[i][2], false); //下
		}
		//对nodes进行排序
		sort(nodes.begin(), nodes.end(), comparator);//按照位置从小到大进行排序

													 //用一个map来高度线及出现的条数，key表示高度，value表示这个高度到现在还有几条
													 //这个map是实时更新的，若某个高度下去了，拿它就会被移除
													 //再用一个map来记录每个位置的最大高度，用于以后生成结果记录
		map<int, int> mapHeightTimes;
		map<int, int> mapPosMaxHeight;


		//把Nodes中的信息加入到mapHeightTimes中
		for (int i = 0; i < 2 * n; i++)
		{
			if (nodes[i]->isUp)
			{
				//若是向上的，那么检查当前Map中是否有这个高度，没有就插入一个，有就将它的value加1
				if (mapHeightTimes.count(nodes[i]->h) == 0)
				{
					mapHeightTimes.insert({ nodes[i]->h, 1 });
				}
				else
				{
					mapHeightTimes[nodes[i]->h]++;
				}
			}
			else
			{
				//若是向下的，那么就检查当前这个高度的次数是否是1，是1的话直接移除，不是的话value-1
				if (mapHeightTimes[nodes[i]->h] == 1)
					mapHeightTimes.erase(nodes[i]->h);
				else
					mapHeightTimes[nodes[i]->h]--;
			}

			//每处理一个元素，就添加一条有关这个位置nodes[i]->pos的信息在mapPosMaxHeight中,key是位置信息，value是这个位置的最大高度
			//若map里面是空的，也就是现在在平地上，那么这个位置的最大高度就是0
			if (mapHeightTimes.empty())
			{
				//需要先检查map里面有没有，没有插入，有就修改，这个Map不能覆盖
				if (mapPosMaxHeight.count(nodes[i]->pos) == 0)
					mapPosMaxHeight.insert({ nodes[i]->pos, 0 });
				else
					mapPosMaxHeight[nodes[i]->pos] = 0;
			}
			else
			{
				//需要先检查map里面有没有，没有插入，有就修改，这个Map不能覆盖
				if (mapPosMaxHeight.count(nodes[i]->pos) == 0)
					mapPosMaxHeight.insert({ nodes[i]->pos, (--mapHeightTimes.end())->first });
				else
					mapPosMaxHeight[nodes[i]->pos] = (--mapHeightTimes.end())->first;
				//mapPosMaxHeight.insert({ nodes[i]->pos, (--mapHeightTimes.end())->first });
			}
		}

		int start = 0;//之前的位置
		int height = 0; //之前的高度
						//根据mapPosMaxHeight生成结果
		for (auto node : mapPosMaxHeight)
		{
			//若是当前的高度与之前的高度一样，那么可以忽略，
			//若是不一样，那么就要进行一番处理了
			if (node.second != height)
			{
				//若是之前的高度是0，那么不足以生成一条结果记录
				//若是不是0
				if (height != 0)
				{
					//若之前不是0，现在和之前还不一样，那么就生成一条新记录
					vector<int> tmp;
					tmp.push_back(start);
					tmp.push_back(node.first);
					tmp.push_back(height);
					res.push_back(tmp);
				}
				start = node.first;
				height = node.second;
			}
		}
		return res;
	}
};

```
   