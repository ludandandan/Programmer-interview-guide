#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Employee{
public:
    int happy; //这名员工可以带来的快乐值
    vector<Employee*> subordinates; //这名员工有哪些直接下级
    Employee(int x):happy(x){}
};

struct ReturnType{
    int comeMax;//头节点来的最大快乐值
    int ncomeMax;//头节点不来的最大快乐值
    ReturnType(int x, int y): comeMax(x), ncomeMax(y){}
};

class Solution{
public:
    int maxHappy(Employee *root)
    {
        if(root==nullptr) return 0;
        ReturnType res = process(root);
        return max(res.comeMax, res.ncomeMax);
    }

    ReturnType process(Employee *root)
    {
        if(root->subordinates.empty())
        {
            ReturnType res(root->happy, 0);
            return res;
        }

        int come = root->happy;//头节点来
        int ncome = 0;
        for(auto node: root->subordinates)
        {
            ReturnType tmp = process(node);
            come += tmp.ncomeMax;//头节点来，其直接下属肯定不来，所以加上不来的最大值
            ncome += max(tmp.comeMax, tmp.ncomeMax); //头节点不来就，下属可以来也可以不来，取最大的
        }
        ReturnType res(come, ncome);
        return res;


    }
};


int main()
{
    Employee A(16);
    Employee B(5);
    Employee C(4);
    Employee D(300);
    Employee E(6);
    Employee F(7);
    Employee G(9);
    Employee H(3);
    Employee I(7);
    Employee J(10);
    Employee K(2);
    Employee L(3);
    Employee M(5);

    A.subordinates.push_back(&B);
    A.subordinates.push_back(&C);
    A.subordinates.push_back(&D);

    B.subordinates.push_back(&E);
    B.subordinates.push_back(&F);
    B.subordinates.push_back(&G);
    
    C.subordinates.push_back(&H);
    C.subordinates.push_back(&I);

    D.subordinates.push_back(&J);
    D.subordinates.push_back(&K);
    D.subordinates.push_back(&L);
    D.subordinates.push_back(&M);

    Solution s;
    int res = s.maxHappy(&A);
    cout << res << endl;
    return 0;
}
