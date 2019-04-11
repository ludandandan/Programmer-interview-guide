#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

void traversing(vector<int> A, vector<int> B);
void binarySearch(vector<int> A, vector<int> B);
void sortB(vector<int> A, vector<int> B);

int main()
{
// A: 1,2,3,4,5
// B: 1,4,2,6,5,7
    string line;
    vector<int> A;
    vector<int> B;
    int i = 0;
    while(getline(cin,line))
    {
        vector<int> num;
        istringstream is(line);
        int n;
        char ch;
        while(is>>n)
        {
            num.push_back(n);
            is >> ch;
        }
        if(i==0) A=num;
        else B=num;
        i++;
    }
    cout << "Method1: Tarversing: ";
    traversing(A, B);
    cout << endl;
    cout << "Method2: BinarySearch: ";
    binarySearch(A,B);
    cout << endl;
    cout << "Method3: SortB: ";
    sortB(A, B);
    cout << endl;
    return 0;
}

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
