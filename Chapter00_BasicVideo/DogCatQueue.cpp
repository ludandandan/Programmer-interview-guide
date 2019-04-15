#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

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
int main()
{   
    Dog dog1;
    Cat cat1;
    Dog dog2;
    Cat cat2;
    Dog dog3;
    Cat cat3;


    DogCatQueue test;
    test.add(dog1);
    test.add(cat1);
    test.add(dog2);
    test.add(cat2);
    test.add(dog3);
    test.add(cat3);

    test.add(dog1);
    test.add(cat1);
    test.add(dog2);
    test.add(cat2);
    test.add(dog3);
    test.add(cat3);
    
    cout << "popDog:" << endl;
    while(!test.isDogEmpty())
    {
        string s = test.popDog().getPetType();
        cout << s << ",";
    }
    cout << endl;
    cout << "popCat:" << endl;
    while(!test.isEmpty())
    {   
        string s = test.popAll().getPetType();
        cout << s << ",";
    }
    cout << endl;
    return 0;
}
