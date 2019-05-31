#include <unordered_map>
#include <map>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

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


int main()
{
	map<int, int> m;

	vector<vector<int>> matrix{ {1,2,3},{ 1,2,4 },{ 1,2,3 },{ 1,2,4 } };
	building b;
	vector<vector<int>> outline = b.buildingOutline(matrix);
	for (auto e : outline)
	{
		for (auto r : e)
		{
			cout << r << ",";
		}
		cout << endl;
	}
	getchar();
	return 0;

}