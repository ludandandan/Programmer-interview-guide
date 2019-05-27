# 找到无序数组中最小的k个数
[完整代码](https://github.com/ludandandan/Programmer-interview-guide/blob/master/Chapter01_AdvancedVideo/bfprt.cpp)

**题目：**

给定一个无序整型数组arr，找到其中最小的k个数

**要求：**

如果数组arr的长度为N，排序之后自然可以得到最小的k个数，此时的时间复杂度与排序的时间复杂度相同，均为O(NlogN)。本题要求实现时间复杂度为O(Nlogk)和O(N)的方法。

## 方法一：使用堆实现：时间复杂度为O(Nlogk)

维护一个大小为k的大根堆（大根堆就是优先级队列priority_queue<int，vector<int>, less<int>）。大根堆的top是里面最大的数。若新来的数比大根堆的top小，就把大根堆的top弹出来，把新数放进去；否则就什么都不做，看下一个新数。

现定义一个大根堆，然后把arr的前k个数放进大根堆，然后依次检查后面的数，若可以放进堆就放进去。遍历完一遍就可以搞定。这时大根堆里的数就是要求最小的前k个数，这时只需要定义一个vector把堆里面的元素都倒出来就可以。


## 方法二：使用BFPRT算法：时间复杂度为O(N)

BFPRT算法是用于求数组中第k小（或大）的数的算法，时间复杂度O(N)。若是找到了第k小的数num，那么只需要遍历一遍数组，把比num小的数放到结果数组res中，若res大小不满足k那么再拿num来填充。这样就可以在O(N)内找到最小的k个数。

注意第K个数是从1开始算的，而数组是从0开始算的，bfprt中的k是指的索引（从0开始算的），所以调用bfprt时的参数应该是k-1。但是好像要是k也无妨，因为会受到res大小为k的限制。

### BFPRT算法：
可以在start到end范围上找第k小的数（从0开始）,这个k是arr的索引，与start和end无关
1. 分组。 对arr中的元素进行分组，5个数一组，最后不足5个数自成一组
2. 组内排序。组内5个数进行排序，可以使用插入排序
3. 构建中位数数组。找到每个组内的中位数，所有组的中位数构建成一个中位数数组mArr
4. 递归调用bfprt(mArr, mArr.size()/2)找到中位数数组的中位数pivot
5. 使用pivot进行partitio操作，返回等于区域（以vector<int>(2)的形式返回等于区域开始的位置bra[0]和结束的位置bra[1]）
6. 检查k是否在等于区域里面，
   1. 若是那么直接返回pivot；
   2. 若k小于bra[0]那么就再在左边进行bfprt
   3. 若k大于bra[1]那么就再在右边进行bfprt.


```c++
class getKNum
{
public:
    //取出最小的k个数，时间复杂度O(N)
    vector<int> getMinKNumByHeap(vector<int> arr, int k)
    {
        vector<int> res;
        if(k<1) return res;
        if(k>arr.size()) return arr;
        priority_queue<int, vector<int>, less<int>> max_heap; //建立大根堆
        for(int i=0; i<k; i++)
        {
            max_heap.push(arr[i]);
        }

        //维护一个大小为k的堆，堆中放目前最小的k个数
        //堆顶是K个数中最大的，若新来的数比堆顶的数小，那么它就要进堆，
        //这时将堆顶的数弹出来，然后再把新来的数放到堆里
        for(int i=k; i<arr.size(); i++)
        {
            if(arr[i]<max_heap.top()) 
            {
                max_heap.pop();
                max_heap.push(arr[i]);
            }
        }
        while(!max_heap.empty())
        {
            res.push_back(max_heap.top());
            max_heap.pop();
        }
        return res;
    }

//先使用bfprt找到第k小的数，然后遍历一遍数组，
//比k小的就放到res数组中，最后res没满的话用第k小的数补齐
    vector<int> getMinKNumByBFPRT(vector<int> arr, int k)
    {
        if(k<1 || k>arr.size()) return arr;
        vector<int> res;
        int kTh = getMinKNumBybfprt(arr, k);
        for(int i=0; i<arr.size(); i++)
        {
            if(arr[i]<kTh) res.push_back(arr[i]);
        }
        //若下面是写的k-1的话这里就会用到，
        //若下面是写的k的话这里就不会用到
        //最好还是写k-1，防止出错
        while(res.size()<k)
        {
            res.push_back(kTh);
        }
        return res;
    }

    int getMinKNumBybfprt(vector<int> arr, int k)
    {
        int n = arr.size();
        vector<int> copyArr(n);
        for(int i=0; i<n; i++) copyArr[i] = arr[i];
        return bfprt(copyArr, 0, n-1, k-1);
    }

    //在begin到end范围上求第k小
    int bfprt(vector<int> &arr, int begin, int end, int k) 
    {
        if(begin==end) return arr[begin];
        //分组；组内排序；取出组内中位数得到中位数数组；
        //从中位数数组中得到中位数的中位数
        int pivot = medianOfMedians(arr, begin, end);
        //使用这个中位数做partition返回等于区域的范围
        //然后检查k是否在等于区域内，若在返回pivot，
        //若不在，看它在哪一边，选一边走
        vector<int> bra = partition(arr, begin, end, pivot);
        if(k>=bra[0] && k<=bra[1]) return arr[k];//也可以返回arr[i]，因为Partition是在数组arr上直接操作的
        else if(k<bra[0])
        {
            return bfprt(arr, begin, bra[0]-1, k);
        }
        else
        {
            return bfprt(arr, bra[1]+1, end, k);
        }
    }

    //partition操作返回等于区域，同时将数组变为荷兰国旗
    //在begin到end范围上做荷兰国旗
    vector<int> partition(vector<int> &arr, int begin, int end, int num)
    {
        vector<int> res(2);
        int less = begin-1; 
        int more = end+1;
        int i = begin;
        while(i<more)
        {
            if(arr[i]<num)
            {
                swap(arr, i++, ++less);
            }
            else if(arr[i]>num)
            {
                swap(arr, i, --more);
            }
            else i++;
        }
        res[0] = less+1;
        res[1] = more-1;
        return res;
    }
    //在begin到end范围上求取中位数的中位数
    int medianOfMedians(vector<int> &arr, int begin, int end)
    {
        if(begin==end) return arr[begin];
        int num = end-begin+1; //范围上有多少数
        int n = num%5==0?num/5:num/5+1;//不是整除就多出来一组
        vector<int> mArr(n);//中位数数组
        for(int i=0; i<n; i++)//共n组，求出每一组的中位数后放在中位数数组里
        {
            int beginI = begin+i*5;
            int endI = beginI+4;
            mArr[i] = getMedian(arr, beginI, min(endI, end));
        }
        //得到中位数数组后，调用bfprt算法得到中位数数组中的中位数
        return bfprt(mArr, 0, mArr.size()-1, mArr.size()/2);
    }

    //获得begin到end范围上的中位数
    int getMedian(vector<int> &arr, int begin, int end)
    {
        if(begin==end) return arr[begin];
        insertSort(arr, begin, end);//先对begin到end范围上的数排序
        int n = begin+end;
        int mid = (n/2)+(n%2);//求中位数所在坐标
        return arr[mid];
    }

    //插入排序，进行组内排序
    void insertSort(vector<int> &arr, int start, int end)
    {
        for(int i=start+1; i<=end; i++)
        {
            for(int j=i-1; j>=start; j--)
            {
                if(arr[j]>arr[j+1]) swap(arr, j, j+1);
                else break;
            }
        }
    }

    void swap(vector<int> &arr, int i, int j)
    {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
};

```