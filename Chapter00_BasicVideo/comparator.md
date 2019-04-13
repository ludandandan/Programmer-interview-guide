## 比较器
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/comparator.cpp)

> 在系统中的综合排序sort()中，会首先检查输入的序列长度是否大于60，如果小于60那么就直接用插入排序。如果大于60，会检查输入的类型是基础类型还是自定义的类型，如果是基础类型那么就用快速排序（无需考虑稳定性），如果是自己定义的类型那么就会用归并排序（可以做到稳定性）。

> 那么什么是排序算法的稳定性?
> 
> 一个排序算法具有稳定性是指其对相同数字排序时能否保持原始的次序不变。
 
> 稳定性有什么意义?
> 稳定性在实际工程中具有重要的意义。例如使用excel表格进行排序，一个类student具有姓名，班级和分数三个数据成员，我们先对分数进行排序，然后对班级进行排序。我们希望在对班级排序时保留原来对分数排序的信息，也就是对同一个班的同学，保持原来分数排序后的次序不变，这样我们就可以得到一个班内的分数排序。

> 当使用sort()对自定义类型进行排序时，需要指定是按照什么规则排序的，否则系统会按照内存地址排序，而这样的排序毫无意义。这个规则的制定就是比较器的定义。

> 常见排序算法的稳定性：
> 
> 1. 冒泡排序：可以做到稳定性。当遇到相同的数字时不进行交换而是直接跳到相同的数字的最后一个。
>
> 2. 选择排序：不具有稳定性。
> 3. 插入排序：可以做到稳定性。当遇到相同的元素时不插到他前面就可以了。
> 4. 归并排序：可以做到稳定性。在merge时遇到相同的元素先往help里放左边的就可以了。
> 5. 快速排序：不具有稳定性。partition的过程无法做到稳定。所有01标准问题在时间复杂度O(N)，空间复杂度O(1)的要求下都无法做到稳定。
> 6. 堆排序：不具有稳定性。堆排序insert元素向上调整时，与沿途的父节点交换，不会关心相同元素的问题。

```c++
struct Student{
    string name;
    int id;
    int score;
    Student(string n, int i, int s): name(n), id(i), score(s){}
};

bool ScoreAscendingComparator(Student o1, Student o2)
{
    return o1.score<o2.score;
}
bool IdAscendingComparator(Student o1, Student o2)
{
    return o1.id<o2.id;
}
int main()
{
    Student A1("LUDan1", 1, 90);
    Student A2("LUDan2", 2, 100);
    Student A3("LUDan3", 1, 87);
    Student A4("LUDan4", 1, 75);
    Student A5("LUDan5", 2, 65);
    vector<Student> v;
    v.push_back(A1);
    v.push_back(A2);
    v.push_back(A3);
    v.push_back(A4);
    v.push_back(A5);
    sort(v.begin(), v.end(), ScoreAscendingComparator);
    for(auto w:v)
    {
        cout << w.name << ",";
    }
    cout << endl; // LUDan5, LUDan4, LUDan3, LUDan1, LUDan2

    sort(v.begin(),v.end(), IdAscendingComparator);
    for(auto w:v)
    {
        cout << w.name << ",";
    }
    cout << endl; //LUDan4, LUDan3, LUDan1, LUDan5, LUDan2
}

```