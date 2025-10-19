#include <iostream>
using namespace std;
const int MAX_SIZE = 100; // 静态分配的最大容量
// 书中List ADT定义
template <class Elem>
class List
{
public:
    virtual bool setPos(int pos) = 0;
    virtual bool insert(const Elem &e) = 0;
    virtual bool remove(Elem &e) = 0;
    virtual bool getValue(Elem &e) const = 0;
};
// 顺序表
template <class Elem>
class AList : public List<Elem>
{
private:
    Elem *listArray;
    int maxSize;
    int listSize; // 目前list中元素的个数
    int fence;    // 栅栏的位置
public:
    AList(int size)
    {
        listArray = new Elem[size];
        maxSize = size;
        listSize = fence = 0;
    }
    ~AList()
    {
        delete[] listArray;
    }
    bool setPos(int pos)
    {
        if ((pos >= 0) && (pos <= listArray)) // pos在合理位置
        {
            fence = pos;
        }
        return (pos >= 0) && (pos <= listArray);
    }
    bool getValue(Elem &it) const // O(1)
    {
        if (fence == listSize)
            return false;
        else
        {
            it = listArray[fence];
            return true;
        }
    }
    bool insert(const Elem &item) // O(n)
    {
        if (listSize == maxSize)
            return false;
        for (int i = listSize; i > fence; i--)
        {
            listArray[i] = listArray[i - 1]; // 后移
        }
        listArray[fence] = item;
        listSize++;
        return true;
    }
    bool remove(Elem &it) // it记录删除值  O(n)
    {
        if (fence == listSize)
        {
            return false;
        }
        it = listArray[fence];
        for (int i = fence; i < listSize; i++)
        {
            listArray[i + 1] = listArray[i + 1];
        }
        listSize--;
        return true;
    }
};
// 常规实现
//  静态数组存储数据
class StaticArrayList
{
private:
    int data[MAX_SIZE];
    int length; // 当前顺序表的长度

public:
    // 构造函数
    StaticArrayList() : length(0) {}

    // 插入元素
    bool insert(int index, int value)
    {
        if (index < 0 || index > length || length >= MAX_SIZE)
        {
            return false; // 插入位置不合法或数组已满
        }
        for (int i = length; i > index; i--)
        {
            data[i] = data[i - 1]; // 将元素后移
        }
        data[index] = value;
        length++;
        return true;
    }

    // 删除元素
    bool remove(int index)
    {
        if (index < 0 || index >= length)
        {
            return false; // 删除位置不合法
        }
        for (int i = index; i < length - 1; i++)
        {
            data[i] = data[i + 1]; // 将元素前移
        }
        length--;
        return true;
    }

    // 查找元素
    int find(int value)
    {
        for (int i = 0; i < length; i++)
        {
            if (data[i] == value)
            {
                return i; // 返回元素位置
            }
        }
        return -1; // 未找到
    }

    // 修改元素
    bool modify(int index, int value)
    {
        if (index < 0 || index >= length)
        {
            return false; // 修改位置不合法
        }
        data[index] = value;
        return true;
    }
};
// 动态数组存储数据
class DynamicArrayList
{
private:
    int *data;
    int capacity; // 当前顺序表的容量
    int length;   // 当前顺序表的长度
    // 扩容函数
    void resize(int newCapacity)
    {
        int *newData = new int[newCapacity];
        for (int i = 0; i < length; i++)
        {
            newData[i] = data[i]; // 复制数据到新数组
        }
        delete[] data; // 释放旧数组
        data = newData;
        capacity = newCapacity;
    }

public:
    // 构造函数
    DynamicArrayList(int initCapacity = 10) : capacity(initCapacity), length(0)
    {
        data = new int[capacity];
    }

    // 析构函数
    ~DynamicArrayList()
    {
        delete[] data;
    }

    // 插入元素
    bool insert(int index, int value)
    {
        if (index < 0 || index > length)
        {
            return false; // 插入位置不合法
        }
        if (length >= capacity)
        {
            resize(capacity * 2); // 扩容
        }
        for (int i = length; i > index; i--)
        {
            data[i] = data[i - 1]; // 将元素后移
        }
        data[index] = value;
        length++;
        return true;
    }

    // 删除元素
    bool remove(int index)
    {
        if (index < 0 || index >= length)
        {
            return false; // 删除位置不合法
        }
        for (int i = index; i < length - 1; i++)
        {
            data[i] = data[i + 1]; // 将元素前移
        }
        length--;
        if (length < capacity / 4)
        {
            resize(capacity / 2); // 缩容
        }
        return true;
    }

    // 查找元素
    int find(int value)
    {
        for (int i = 0; i < length; i++)
        {
            if (data[i] == value)
            {
                return i; // 返回元素位置
            }
        }
        return -1; // 未找到
    }

    // 修改元素
    bool modify(int index, int value)
    {
        if (index < 0 || index >= length)
        {
            return false; // 修改位置不合法
        }
        data[index] = value;
        return true;
    }
};

// 链表
template <class Elem>
class Node
{
public:
    Elem element;
    Node *next;
    Node(const Elem &elemval, Node *nextval = NULL)
    {
        element = elemval;
        next = nextval;
    }
};
template <class Elem>
class LList : public List<Elem>
{
private:
    Node<Elem> *head;
    Node<Elem> *tail;
    Node<Elem> *fence; // 指向栅栏的前一个结点
    int length;

public:
    LList()
    {
        fence = head = tail = new Node<Elem>; // 头结点 表示链表的开始
        length = 0;
    }
    bool getValue(Elem &it) const
    {
        if (fence == tail)
        {
            return false;
        }
        it = fence->next->element; // 当前结点的值 fence为当前结点的上一个结点 fence->next则为当前结点
        return true;
    }
    bool insert(const Elem &item) // O(1)
    {
        fence->next = new Node<Elem>(item, fence->next); // 创建结点 新结点变为当前结点 值为加入的值 指向原来的当前结点
        if (tail == fence)
        {
            tail = fence->next; // new tail
        }
        length++;
        return true;
    }
    bool remove(Elem &it) // O(1)
    {
        if (fence->next == NULL)
            return false;
        it = fence->next->element;
        Node<Elem> *ltemp = fence->next; // remove
        fence->next = ltemp->next;       // 修改当前结点
        if (tail == ltemp)
        {
            tail = fence;
        }
        delete ltemp; // reclaim space
        length--;
        return true;
    }
    bool setPos(int pos) // O(n)
    {
        if ((pos < 0) || (pos > length))
        {
            return false;
        }
        fence = head;                 // 从前往后调整
        for (int i = 0; i < pos; i++) // pos次移动
        {
            fence = fence->next;
        }
        return true;
    }
};
