#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
using namespace std;

//归并排序
void MergeSort(int *a, int l, int r)
{
    if (r - l <= 1)
        return;

    // 分解
    int mid = l + ((r - l) >> 1);
    MergeSort(a, l, mid), MergeSort(a, mid, r);

    // 合并
    std::vector<int> tmp(r - l); // 使用 vector 来避免数组越界问题

    merge(a + l, a + mid, a + mid, a + r, tmp.data()); // a+l为指针  tmp.data()内部数组的第一个元素的指针。
    for (int i = l; i < r; ++i)
        a[i] = tmp[i - l];
}
void merge(int *l, int *l_end, int *r, int *r_end, int *result)
{
    while (l != l_end && r != r_end)
    {
        if (*l < *r)
        {
            *result++ = *l++;
        }
        else
        {
            *result++ = *r++;
        }
    }
    while (l != l_end)
    {
        *result++ = *l++;
    }
    while (r != r_end)
    {
        *result++ = *r++;
    }
}


