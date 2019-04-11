## 找出B中不属于A的元素并打印
[完整代码]()

**题目：** 
> 有一个有序数组A，一个无序数组B，请打印B中所有不在A中的数。A的数组长度为N，B的数组长度为M，写出算法并分析其复杂度。

* **方法1：遍历**

> 遍历B数组，把B中每个元素取出来与A中元素对比，若在A中找了一圈没找到则打印这个元素。B中每个元素都需要将A遍历一遍，时间复杂度O(M*N)
```c++
void traversing(vector<int> A, vector<int> B)
{
    int na = A.size();
    int nb = B.size();
    for(int i=0; i<nb; i++)
    {
        int b = B[i];
        int j = 0;
        for(; j<na; j++)
        {
            if(b==A[j]) break;
        }
        if(j==na) cout << b << ",";
    }
    return;
}
```
* **方法2：二分查找**

> 由于A数组是有序的，在一个有序数组中查找某个元素可以使用二分查找的方法。仍需遍历B，将B中每个元素取出来使用二分搜索的方式在A中查找。时间复杂度O(M*log(N))。
```c++
void binarySearch(vector<int> A, vector<int> B)
{
    int na = A.size();
    int nb = B.size();
    for(int i=0; i<nb; i++)
    {
        int b = B[i];
        int left = 0; 
        int right = na-1;
        while(left<=right)
        {
            int mid = left+(right-left)/2;
            if(b==A[mid]) break;
            else if(b<A[mid]) right = mid-1;
            else left = mid+1;
        }
        if(left>right) cout << b << ",";
    }
    return;
}
```
* **方法3: 对B排序，再用类似外排的方式查找**

> 先对B数组进行排序，然后采用类似外排的方式进行查找。引入两个指针a,b分别指向A和B数组的第一个元素，若a指向的元素等于b指向的元素，则b++(若确定B中无重复元素也可同时a++)， 若a指向的元素小于b指向的元素，则a++，若a指向的元素大于b指向的元素则打印b指向的元素后b++。这个过程一直进行直到a或b中的任何一个超出A或B的索引。若跳出之后，b还没有超出B的索引，则b和b之后的元素都不属于A，全部打印。
```c++
void sortB(vector<int> A, vector<int>B)
{
    int na = A.size();
    int nb = B.size();
    sort(B.begin(), B.end());
    int i=0, j=0;
    while(i<na && j<nb)
    {
        if(A[i]==B[j]) {j++;}//B中可含重复元素
        else if(A[i]<B[j]) i++;
        else 
        {
            cout << B[j++] << ",";
        }
    }
    while(j<nb)
    {
        cout<<B[j++] << ",";
    }
    return;
}
```