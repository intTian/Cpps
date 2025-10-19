#include <iostream>
using namespace std;

// 希尔排序
template <class Elem>
void shellsort(Elem A[], int n)
{
    for (int incr = n / 2; incr >= 1; incr /= 2;)
    {
        for (int k = 0; k < incr; k++) // 排序第k个子序列
        {
            inssort2<Elem>(A, n, incr, k);
        }
    }
}

// incr 增量 子序列的数目
template <class Elem>
void inssort2(Elem A[], int n, int incr, int k)
{
    int from = k;
    for (int i = from + incr; i < n; i += incr)
    {
        for (int j = i(j > from & A[j] < A[j - incr]); j -= incr)
        {
            swap(A, j, j - incr);
        }
    }
}