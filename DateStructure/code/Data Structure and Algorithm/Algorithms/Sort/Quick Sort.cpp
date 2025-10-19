#include <iostream>
using namespace std;

// 快速排序
template <class Elem>
void qsort(Elem A[], int i, int j) // i为左边界 j为右边界
{
    if (j <= i)
    {
        return;
    }
    int pivot = findpivot(A, i, j);
    swap(A, pivot, j); // 将支点放在最后
    int k = partition(A, i, j, A[j]);
    swap(A, k, j); // 将支点放回
    qsort<Elem>(A, i, k - 1);
    qsort<Elem>(A, k + 1, j);
} 
template <class Elem>
int findpivot(Elem A[], int i, int j)
{
    return (i + j) / 2; // 返回中间元素
}
template <class Elem>
int partition(Elem A[], int l, int r, Elem &pivot)
{
    do
    { // 双指针记录位置
        while (A[l] < pivot)
        {
            l++;
        }
        while ((r > l) && A[r] >= pivot)
        {
            r--;
        }
        swap(A, l, r);
    } while (l < r);
    return l;
}