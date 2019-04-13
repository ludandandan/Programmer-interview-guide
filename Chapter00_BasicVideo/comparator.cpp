#include <cstdio>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

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
