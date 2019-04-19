## 设计RandomPool结构
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/RandomPool.cpp)

**题目：**

>  设计一种结构，在该结构中有如下功能：
> 1. insert(key)：将某个key加入到该结构中，做到不重复加入。
> 2. delete(key)：将原本在结构中的某个key移除。
> 3. getRandom()：等概率的随机返回结构中的任何一个key。
>   
> 要求：insert, delete, getRandom方法的时间复杂度都是O(1)。

> 使用两个哈希表来构造这个结构。一个哈希表不能完成这个任务，虽然哈希表具有输入不同，输出在S域上具有均匀性，但是并不是严格等概率，尤其是输入样本量很小时更不能保证。
> 本结构的实现需要两个哈希表map1和map2，和一个int类型的变量size用于记录哈希表中的元素个数。
> 1. insert(key)添加：假设本题的key是string类型的。map1中保存<string, int>类型的key和index，表示这个key是第index个进哈希表的，同时map2中保存<int, string>类型，表示第index个进哈希表的是key。size初始值0，进来一个key，size++。
> 2. getRandom()：根据size使用rand函数生成一个[0,size-1]范围的随机数rand_index，返回map2中rand_index对应的value。
> 3. delete(key)删除：若是直接删除给定的key所对应的在map1和map2中的两条记录，那么再以后getRandom时，在[0,size-1]范围上会产生洞。为了解决这个问题，可以用最后一条记录去补这个空洞，这样size--之后在[0,size-1]范围上仍然是连续的。先根据size在map2取出最后一条记录的lastString，根据key在map1中取出这个key对应的index，在map1中将key对应的记录删除，将lastString对应的记录删除，在map2中将index和lastindex对应的记录删除。然后在map1中添加{lastString,index}记录，在map2中添加{index, lastString}记录。搞定。

```c++
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
```