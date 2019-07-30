#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

double get_edge(double x1, double y1, double x2, double y2);
double maxGY(double x, double y);


int main()
{
	int T; //T组测试用例
	double PI = 3.1415926;
	double x1, x2, x3, y1, y2, y3;//三个点的横纵坐标
	double a, b, c; //三角形三条边
	double A, B, C; //三角形角度的弧度值
	double r; //三角形最小外接园的半径
	double S; //三角形的面积
	double n; //n边形的边数. n也要用double,不然就自动向下取整了
	double Sn; //正n边形的面积
	cin >> T;
	while (T > 0)
	{
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		//根据三个点坐标计算三条边长
		a = get_edge(x1, y1, x2, y2);
		b = get_edge(x1, y1, x3, y3);
		c = get_edge(x2, y2, x3, y3);

		//计算周长的一半为海伦公式计算三角形面积做准备
		double p = (a + b + c) / 2;
		//海伦公式计算三角形面积
		S = sqrt(p*(p - a)*(p - b)*(p - c));
		//计算三角形最小外接矩形的半径
		r = a * b*c / 4 / S;

		//计算三条边所对应的角cosA = (b^2+c^2-a^2)/(2bc)
		A = acos((b*b + c * c - a * a) / (2 * b*c));
		B = acos((a*a + c * c - b * b) / (2 * a*c));
		C = acos((a*a + b * b - c * c) / (2 * a*b));

		//求三个角的公因数
		double tmp = maxGY(A, B);
		tmp = maxGY(tmp, C);

		//求正多边形的边数。
		n = PI / tmp;
		//计算正多边形面积，共n个边长为r的等腰三角形，每个三角形面积1/2*a*b*sin(C)
		Sn = (r*r / 2)*sin(2 * PI / n)*n;
		printf("%.6f\n", Sn);
		T--;
	}
	return 0;

}


//求边长
double get_edge(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//辗转相除法求最大公约数
//辗转相除法求最大公约数=求最大公约数（大数%小数，小数），直到其中一个数到0了，那么此时的另一个数就是最大公约数
//由于数是double类型，没办法直接到0，定义一个精度为0.001，当一个数比0.001小了那么就可以认为到0 了。
//精度取决于n的最大到多少，取1/n比较合适
double maxGY(double x, double y)
{
	while (fabs(x) > 0.0001 && fabs(y) > 0.0001)
	{
		if (x > y)
		{
			x = x - floor(x / y)*y;
		}
		else
		{
			y = y - floor(y / x)*x;
		}
	}
	return x + y;
}