#include <cstdio>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

struct Student{
    string name;
    int id;
    int score;
    Student(string n, int i, int s): name(n), id(i), score(s){}
};

bool ScoreAscendingComparator(Student o1, Student o2)
{
    return o1.score<o2.score; //得分少的放在前面
}
struct ScoreLessComparator{
    bool operator() (Student o1, Student o2)
    {
        return o1.score<o2.score; //less是大根堆
    }
};

struct ScoreGreaterComparator{
    bool operator() (Student o1, Student o2)
    {
        return o1.score>o2.score;//greater是小根堆
    }
};

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

    //建立降序队列，大根堆
    priority_queue<Student, vector<Student>, ScoreLessComparator> MaxHeap;
    MaxHeap.push(A1);
    MaxHeap.push(A2);
    MaxHeap.push(A3);
    MaxHeap.push(A4);
    MaxHeap.push(A5);

    cout << "MaxHeap: " << endl;
    while(!MaxHeap.empty())
    {
        cout << MaxHeap.top().name << ",";
        MaxHeap.pop();
    }
    cout << endl;// LUDan2, LUDan1, LUDan3, LUDan4, LUDan5

    //建立小根堆
    priority_queue<Student, vector<Student>, ScoreGreaterComparator> MinHeap;
    MinHeap.push(A1);
    MinHeap.push(A2);
    MinHeap.push(A3);
    MinHeap.push(A4);
    MinHeap.push(A5);

    cout << "MinHeap: " << endl;
    while(!MinHeap.empty())
    {
        cout << MinHeap.top().name << ",";
        MinHeap.pop();
    }
    cout << endl; // LUDan5 LUDan4, LUDan3, LUDan1, LUDan2
}
