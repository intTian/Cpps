#include <iostream>
using namespace std;
// 定义顺序表结构
struct SeqList
{
    int *elem;  // 存储元素的数组
    int length; // 当前长度
};

// 顺序查找
int Sequential_Search(int *a, int n, int key)
{
    int i;
    a[0] = key; // 设置a[0]为关键字，称之为“哨兵”
    i = n;      // 循环从数组尾部开始
    while (a[i] != key)
    {
        i--;
    }
    return i; // 返回0则说明查找失败
}

// 折半查找 对于有序数组
int Binary_Search(SeqList L, int key)
{
    int low = 0, high = L.length - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2; // 取中间位置
        if (L.elem[mid] == key)
        {
            return mid; // 查找成功返回所在位置
        }
        else if (L.elem[mid] > key)
        {
            high = mid - 1; // 从前半部分继续查找
        }
        else
        {
            low = mid + 1; // 从后半部分继续查找
        }
    }
    return -1; // 查找失败，返回-1
}

// 插值查找 对于有序数组
int Binary_Search(SeqList L, int key)
{
    int low = 0, high = L.length - 1, mid;
    while (low <= high)
    {
        mid = low + (key - L.elem[low]) / (L.elem[high] - L.elem[low]) * (high - low); // 插值
        if (L.elem[mid] == key)
        {
            return mid; // 查找成功返回所在位置
        }
        else if (L.elem[mid] > key)
        {
            high = mid - 1; // 从前半部分继续查找
        }
        else
        {
            low = mid + 1; // 从后半部分继续查找
        }
    }
    return -1; // 查找失败，返回-1
}

// 斐波那契查找
int Fibonacci_Search(int *a, int n, int key)
{
    int low, high, mid, i, k;
    low = 0;  // 定义最低下标为记录首位
    high = n; // 定义最高下标为记录末尾
    k = 0;
    while (n > F(k) - 1)
    {
        // 计算n位于斐波那契数列的位置
        k++;
    }
    for (i = n; i < F(k); i++)
    {
        // 在尾部补上F[k]-n-1个数，大小等于尾部最大值，否则会存在数组溢出
        a[i] = a[n];
    }
    while (low <= high)
    {
        mid = low + F(k - 1) - 1; // 计算当前分隔的下标
        if (key < a[mid])
        {
            // 若查找记录小于当前分隔记录
            high = mid - 1; // 最高下标调整到分隔下标mid-1处
            k = k - 1;      // 斐波那契数列下标减一位
        }
        else if (key > a[mid])
        {
            // 若查找记录大于当前分隔记录
            low = mid + 1; // 最低下标调整到分隔下标mid+1处
            k = k - 2;     // 斐波那契数列下标减两位
        }
        else
        {
            if (mid <= n)
            {
                return mid; // 若相等则说明mid即为查找的位置
            }
            else
            {
                return n; // 若mid>n说明是补全数值，返回n
            }
        }
    }
    return -1;
}
// 递归实现斐波那契数列
int F(int n)
{
    if (n == 0)
        return 0; // 基准条件
    if (n == 1)
        return 1;               // 基准条件
    return F(n - 1) + F(n - 2); // 递归调用
}