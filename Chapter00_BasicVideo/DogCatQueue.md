## 猫狗队列
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter00_BasicVideo/CatDogQueue.cpp)

**题目：**
>宠物，狗和猫的类如下(java代码)：
```java
public class Pet{
    private String type;
    public Pet(String type){
        this.type = type;
    }
    public String getPetType(){
        return this.type;
    }
} 
public class Dog extends Pet{
    public Dog(){
        super("dog");
    }
}
public class Cat extends Pet{
    public Cat(){
        super("cat");
    }
}
```
> 实现一种猫狗队列的结构，要求如下：
> 1. 用户可以调用add方法将cat类或dog类的实例放入队列中；
> 2. 用户可以调用pollAll方法，将队列中所有实例按照进队列的先后顺序依次弹出；
> 3. 用户可以调用pollDog方法，将队列中的dog类的实例按照进队列的先后顺序依次弹出；
> 4. 用户可以调用pollDog方法，将队列中的dog类的实例按照进队列的先后顺序依次弹出；
> 5. 用户可以调用isEmpty方法，检查队列中是否有dog或cat类的实例；
> 6. 用户可以调用isDogEmpty方法，检查队列中是否有dog类的实例；
> 7. 用户可以调用isCatEmpty方法，检查队列中是否有cat类的实例；

> 可以使用现成的队列结构构建一个cat队列，一个dog队列。
> 
> 对于add方法：当来的实例是cat类是push进入cat队列，若是dog类进入dog队列。
>
> 对于pollDog方法和pollDog方法只需将相应的实例pop出相应的队列即可，同时注意再pop出来之前需要保存top的实例，因为poll还要求返回top的实例。
> 
> 对于pollAll方法，就需要一个计数器，用于为每一个进来的宠物打上时间戳，比较cat队列和dog队列的top看哪个时间比较早就弹出哪个。但是计数器不能添加在题目给定的Pet，Dog，和Cat类中，我们需要新建一个类PetEnter，在这个自己定义的类中添加时间戳。所有前面所说的cat队列和dog队列的的元素不是上层给的Pet类，而是自定义的PetEnter类。为了满足题目要求，poll的所有方法返回的应该是Pet类，故在PetEnter类中我们需要一个getPet的方法以便后续的返回。
> 
> 当然还需要定义一个猫狗队列类CatDogQueue，这是题目要实现的结构。定义PetEnter只是为了加入时间戳辅助猫狗队列结构的完成。
> 通过这个题目对类的定义和使用有了初步认识。

```c++
class Pet{
public:
    string type;
    Pet(string t):type(t){}
    string getPetType()
    {
        return type;
    }
};

class Dog : public Pet{
public:
    Dog(): Pet("dog"){}
};
class Cat : public Pet{
public:
    Cat(): Pet("cat"){}
};

//定义一个宠物进的类型，在Pet类型的基础上再加上一个计数项作为时间戳
class PetEnter{
private:
    Pet pet;
    long count;
public:
    PetEnter(Pet p, long c): pet(p),count(c){}
    Pet getPet()
    {
        return pet;
    }
    long getCount()
    {
        return count;
    }
    string getEnterPetType()
    {
        return pet.getPetType();
    }
};

class DogCatQueue{
private:
    queue<PetEnter> dogQueue;
    queue<PetEnter> catQueue;
    long count;
public:
    DogCatQueue():count(0){}
    void add(Pet pet)
    {
        if(pet.getPetType()=="dog")
        {
            PetEnter p(pet, count++);
            dogQueue.push(p);
        }
        else if(pet.getPetType()=="cat")
        {
            PetEnter p(pet, count++);
            catQueue.push(p);
         }
        else throw runtime_error("not dog and cat!");
    }

    Pet popAll()//弹出并返回所有宠物中最早的一个
    {
        if(!dogQueue.empty() && !catQueue.empty())
        {
            if(dogQueue.front().getCount() < catQueue.front().getCount())
            {
                Pet p = dogQueue.front().getPet();
                dogQueue.pop();
                return p; 
            }
            else
            {
                Pet p = catQueue.front().getPet();
                catQueue.pop();
                return p;
            }
        }
        else if(!dogQueue.empty())
        {
            Pet p = dogQueue.front().getPet();
            dogQueue.pop();
            return p;
        }
        else if(!catQueue.empty())
        {
            Pet p = catQueue.front().getPet();
            catQueue.pop();
            return p;
        }
        else throw runtime_error("the queue is empty!");
    }

    Pet popDog()
    {
        if(dogQueue.empty()) throw runtime_error("the Dog queue is empty!");
        else
        {
            Pet p = dogQueue.front().getPet();
            dogQueue.pop();
            return p;
        }
    }

    Pet popCat()
    {
        if(catQueue.empty()) throw runtime_error("the Cat queue is empty!");
        else
        {
            Pet p = catQueue.front().getPet();
            catQueue.pop();
            return p;
        }
    }

    bool isEmpty()
    {
        return dogQueue.empty()&&catQueue.empty();
    }

    bool isCatEmpty()
    {
        return catQueue.empty();
    }

    bool isDogEmpty()
    {
        return dogQueue.empty();
    }
        
};
```