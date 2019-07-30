#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

int main()
{
	int T;
	int N, M, a;
	cin >> T;
	while (T > 0)
	{
		cin >> N >> M >> a;
		//重要提醒：要用long类型，虽然输入没有超出int，但是两个数的乘积就有可能超出了
		long x, y;
		x = ceil(double(N) / double(a));
		y = ceil(double(M) / double(a));
		cout << x * y << endl;
		T--;
	}
	return 0;
}