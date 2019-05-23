#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
using namespace std;

class Solution{
public:
    bool isUniquel(vector<char> vc)
    {
        if(vc.empty() || vc.size()==1) return true;
        unordered_map<char, int> m;
        for(auto c: vc)
        {
            if(m.count(c)==0) m[c] = 1;
            else return false;
        }
        return true;
    }

    //时间复杂度O(Nlog(N)) , 额外空间复杂度O(1)
    bool isUniquel2(vector<char> vc)
    {
        if(vc.empty() || vc.size()==1) return true;
        heapSort(vc);
        for(int i=1; i<vc.size(); i++)
        {
            if(vc[i]==vc[i-1]) return false;
        }
        return true;
    }

    void heapSort(vector<char> &vc)
    {
        if(vc.size()<2) return;
        for(int i=1; i<vc.size(); i++)
        {
            heapInsert(vc, i);
        }
        for(int i=vc.size()-1; i>0; i--)
        {
            swap(vc, 0, i);
            heapify(vc, 0, i);
        }
    }

    void swap(vector<char> &vc, int i, int j)
    {
        char tmp = vc[i];
        vc[i] = vc[j];
        vc[j] = tmp;
    }

    //从下向上
    void heapInsert(vector<char> &vc, int index)
    {
        while(index>0)
        {
            int parent_index = (index-1)/2;
            if(vc[parent_index]<vc[index])
            {
                swap(vc, parent_index, index);
                index = parent_index;
            }
            else break;
        }
    }
    
    //从上向下
    void heapify(vector<char> &vc, int index, int heapSize)
    {
        int left_index = index*2+1;
        int right_index = index*2+2;
        while(left_index<heapSize)
        {
            int largest = right_index<heapSize && vc[right_index]>vc[left_index]? right_index:left_index;
            if(vc[index]>vc[largest]) break;
            else
            {
                swap(vc, index, largest);
                index = largest;
                left_index = index*2+1;
                right_index = index*2+2;
            }
        }
    }
};

int main()
{
    Solution s;
    vector<char> vc{'1','2','a', 'b', '1'};
    bool res = s.isUniquel(vc);
    cout << res << endl;
    bool res2 = s.isUniquel2(vc);
    cout << res2 << endl;
    return 0;
}
