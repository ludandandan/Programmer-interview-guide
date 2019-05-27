#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

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


class test{
public:
    vector<int> getMinKNumsByBFPRT(vector<int> arr, int k)
    {
        //这里的k是从1开始，数组里是从0开始
        if(k<1 || k>arr.size()) return arr;
        vector<int> res;
        int minKth = getMinKthByBFPRT(arr, k);
        for(int i=0; i<arr.size(); i++)
        {
            if(arr[i]<minKth) res.push_back(arr[i]);
        }
        while(res.size()<k)
        {
            res.push_back(minKth);
        }
        return res;
    }

    int getMinKthByBFPRT(vector<int> arr, int k)
    {
        //将arr复制一遍
        int n = arr.size();
        vector<int> arrCopy(n);
        for(int i=0; i<n; i++) arrCopy[i] = arr[i];
        return bfprt(arr, 0, n-1, k-1);
    }

    //从start到end上找到第k小的数,k是arr上索引为k的数，与start,end无关
    int bfprt(vector<int> &arr, int start, int end, int k)
    {
        if(start==end) return arr[start];
        //分组，组内排序，得到每组中位数组成新组，然后得到中位数的中位数
        int pivot = medianOfMedians(arr, start, end);
        //在start到end范围上找到中位数的中位数作为partition的分割
        //在start到end范围上使用pivot进行partition分割返回等于区域
        vector<int> bra = partition(arr, start, end, pivot);
        if(k>=bra[0] && k<=bra[1]) return arr[k];//因为partition是直接在arr上进行的
        else if(k<bra[0])
        {
            return bfprt(arr, start, bra[0]-1, k);
        }
        else
        {
            return bfprt(arr, bra[1]+1, end, k);
        }
    }


    //获得中位数数组的中位数
    int medianOfMedians(vector<int> &arr, int start, int end)
    {
        //分组
        int n = end-start+1; //一共对多少数分组
        int m = n%5==0?(n/5):(n/5+1); //一共分多少组
        //中位数数组
        vector<int> mArr(m);
        //5个数一组求中位数并放到中位数数组中
        for(int i=0; i<m; i++)
        {
            int startI =start+i*5;
            int endI = startI+4;
            mArr[i] = getMedian(arr, startI, min(endI, end));
        }
        return bfprt(mArr, 0, mArr.size()-1, mArr.size()/2);
    }

    //获得中位数
    int getMedian(vector<int> &arr, int start, int end)
    {
        if(start==end) return arr[start];
        //从start到end进行插入排序
        insertSort(arr, start, end);
        int n = start + end;
        int mid = (n/2) + (n%2);
        return arr[mid];
    }

    //partition
    vector<int> partition(vector<int> &arr, int start, int end, int pivot)
    {
        int less = start-1;
        int more = end+1;
        int i=start;
        while(i<more)
        {
            if(arr[i]<pivot)
            {
                swap(arr, i++, ++less);
            }
            else if(arr[i]>pivot)
            {
                swap(arr, i, --more);
            }
            else i++;
        }
        vector<int> bra(2);
        bra[0] = less+1;
        bra[1] = more-1;
        return bra;
    }

    //从start到end进行插入排序
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
    //交换
    void swap(vector<int> &arr, int i, int j)
    {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    vector<int> getMinKNumsByheap(vector<int> arr, int k)
    {
     //维护一个大小为k的大根堆，
     //若新来的数比大根堆的堆顶小的话就把堆顶弹出来，把新数放进去
     //若新来的数不如大根堆的堆顶小，那么就直接忽略
     //堆就是优先级队列
        priority_queue<int, vector<int>, less<int>> heap;
        //先把前k个数放进堆里
        for(int i=0; i<k; i++)
        {
            heap.push(arr[i]);
        }
        //对其他数，小的进堆
        for(int i=k; i<arr.size(); i++)
        {
            if(arr[i]<heap.top())
            {
                heap.pop();
                heap.push(arr[i]);
            }
        }
        vector<int> res;
        while(!heap.empty())
        {
            int i = heap.top();
            heap.pop();
            res.push_back(i);
        }
        return res;
    }
};

int main()
{
    vector<int> arr{13, 24, 1, 5,32,767,3,63,390};
    getKNum n;
    vector<int> res = n.getMinKNumByHeap(arr, 3);
    for(auto r: res)
    {
        cout << r << ",";
    }
    cout << endl;
    vector<int> res2 = n.getMinKNumByBFPRT(arr, 3);
    for(auto r: res2)
    {
        cout << r << ",";
    }
    cout << endl;
    test t;
    vector<int> res3 = t.getMinKNumsByBFPRT(arr, 3);
    for(auto r: res3)
    {
        cout << r << ",";
    }
    cout << endl;
    vector<int> res4 = t.getMinKNumsByheap(arr, 3);
    for(auto r: res4)
    {
        cout << r << ",";
    }
    cout << endl;
    return 0;
}
