#include <iostream>
using namespace std;

// 堆
// 最大堆
template <class Elem>
class maxheap
{
private:
    Elem *Heap;
    int size; // 一共数组的大小
    int n;    // 实际结点的个数

public:
    maxheap(Elem *h, int num, int max)
    {
        Heap = h;
        n = num;
        size = max;
        buildHeap();
    }
    // 堆的构建O(n)
    void buildHeap()
    {
        for (int i = (n / 2) - 1; i >= 0; i--) // 从最后的中间结点从后往前进行下拉
        {
            siftdown(i);
        }
    }
    // siftdown向下调整O(logn)
    void siftdown(int pos)
    {
        while (!isLeaf(pos)) // 直到pos为叶节点或者满足最大堆的性质
        {
            int j = leftchild(pos);
            int rc = rightchild(pos);
            if ((rc < n) && Heap[j] < Heap[rc])
            {
                j = rc; // j为较大的那个孩子
            }
            if (Heap[pos] >= Heap[j]) // 满足最大堆的性质
            {
                return;
            }
            swap(Heap, pos, j);
            pos = j; // 将pos重新指向调换的位置
        }
    }

    // 删除 堆顶 最大值 O(logn)
    bool removemaxHeap(Elem &it)
    {
        if (n == 0)
        {
            return false;
        }
        swap(Heap, 0, --n); // n-1为最后的一个叶节点 n=n-1 数组大小减一

        if (n != 0)
        {
            siftdown(0);
        }

        it = Heap[n];
        return true;
    }

    // 插入 O(logn)
    bool insert(const Elem &val)
    {
        if (n >= size)
        {
            return false;
        }
        
        int curr = n++; // 记录插入的位置 数组大小加一 插入到数组末尾 然后上拉
        
        Heap[curr] = val;
        // 上提 直到curr的父亲大于等于curr或者curr上提至根节点
        while (curr != 0 && Heap[curr] > Heap[parent(curr)])
        {
            swap(Heap, curr, parent(curr));
            curr = parent(curr);
        }
        return;
    }
    int leftchild(int pos)
    {
        return 2 * pos + 1;
    }
    int rightchild(int pos)
    {
        return 2 * pos + 2;
    }
    int parent(int pos)
    {
        return (pos - 1) / 2;
    }
    bool isLeaf(int pos) // 是否为叶节点
    {
        return (pos >= n / 2) && (pos < n);
    }
};
