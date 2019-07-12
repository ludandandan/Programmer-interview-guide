# 派对的最大快乐值
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/maxHappy.cpp)

**题目：**
员工信息的定义如下：
```c++
class Employee{
public:
    int happy; //这名员工可以 带来的快乐值
    List<Employee> subordinates; //这名员工有哪些直接下级
};
```

公司的每个员工都符合Employee类的描述，整个公司的人员结构可以看作是一棵标准的，没有环的多叉树。树的头节点是公司唯一的老板，除老板外，每个员工都有唯一的直接上级。叶节点是没有任何下属的基层员工(subordinates列表为空)，除基层员工外，每个员工都有一个或多个直接下级。

这个公司现在要半party，你可以决定哪些员工来，哪些员工不来。但是要遵循如下规则：
 
1. 如果一个员工来了，那么他的所有直接下级都不能来
2. 派对的整体快乐值是所有到场的员工的快乐值的累加
3. 你得目标是让派对的整体快乐值尽量大

给定一个头节点boss，请返回派对的最大快乐值

**要求：**
    如果以boss为头节点的整棵树有N个节点，请做到时间复杂度O(N)

**解析：**

分析可能性：
以x为头的树有两种可能：

    1. x来， 那么它的直接下级肯定不来
    2. x不来， 那么它的直接下级可以选择来或者不来
    
    分别计算x来时的最大快乐值和x不来时的最大快乐值，从这两种可能中取最大的

设计返回结构：
    1. 根节点x来时的最大快乐值，comeMax
    2. 根节点x不来时的最大快乐值，ncomeMax

那么base case就是对于基层员工，他们来的快乐值就是happy，不来的快乐值就是0.

对于其他位置，来的快乐值就是其所有下属不来时的最大快乐值相加； 不来的快乐值就是其所有下属max(comeMax, ncomeMax)相加

```c++
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
```
