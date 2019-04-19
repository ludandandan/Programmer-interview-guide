#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <cstdlib>
using namespace std;

class RandomPool{
private:
    unordered_map<string, int> map1;
    unordered_map<int, string> map2;
    int size=0;
public:
    //RandomPool():map1(new unordered_map<string, int>), map2(new unordered_map<int, string>), size(0){}
    void add(string key)
    {
        if(map1.find(key)!=map1.end()) return;
        map1.insert({key, size});
        map2.insert({size++, key});
    }
    string getRandom()
    {
        if(size==0) return NULL;
        srand(time(NULL));
        int rand_index = rand()%size; //获得一个[0,size-1]上的一个数
        return map2[rand_index];
    }
    void mydelete(string key)
    {
        if(map1.find(key)==map1.end()) return; //如果map1中没有这个key就直接返回
        int index = map1[key];
        int lastindex = --size;
        string lastString = map2[lastindex];
        map1.erase(key);
        map1.erase(lastString);
        map2.erase(index);
        map2.erase(lastindex);
        map1.insert({lastString, index});
        map2.insert({index, lastString});
    }
};

int main()
{
    RandomPool r1;
   // r1.add("LUDan");
   // r1.add("Zhxt");
   // r1.add("z");
   // cout << r1.getRandom() << endl;
   // r1.mydelete("z");
   // cout << r1.getRandom() << endl;
   // r1.mydelete("LUDan");
   // cout << r1.getRandom() << endl;
    string s;
    while(cin>>s)
    {
        r1.add(s);
        cout << "getRandom: " <<  r1.getRandom() << endl;
    }
    return 0;
}
