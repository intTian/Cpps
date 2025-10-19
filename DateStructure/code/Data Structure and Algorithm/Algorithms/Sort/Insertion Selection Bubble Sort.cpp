#include <iostream>
using namespace std;

// 以下的排序算法时间都为 O(n的平方)
//  插入排序
template <class Elem>
void inssort(Elem A[], int n)
{
    for (int i = 1; i < n; i++) // 先抽了0号为开始元素 从1号开始
    {
        // 插入第i号元素
        for (int j = i; j > 0 && A[j] < A[j - 1]; j--)
        {
            swap(A, j, j - 1); // 交换
        }
    }
}

// 选择排序
template <class Elem>
void selsort(Elem A[], int n)
{
    for (int i = 0; i < n - 1; i++) // n-1次操作 选择n-1个最小
    {
        // 在A[i,n-1]中选择最小
        int min = i;                         // 记录最小的位置
        for (int j = i + 1; j <= n - 1; j++) // 从i+1到n-1全部依次比较
        {
            if (A[j] < A[min])
            {
                min = j; // 更新最小值的位置
            }
            // 交换
            swap(A, i, min);
        }
    }
}

// 冒泡排序
template <class Elem>
void bubble(Elem A[], int n)
{
    for (int i = 0; i < n - 1; i++) // 一共n-1次冒泡
    {
        for (int j = n - 1; j > i; j--) // 从数组最后开始冒泡
        {
            if (A[j] < A[j - 1]) // 较小则交换
            {
                swap(A, j, j - 1);
            }
        }
    }
}