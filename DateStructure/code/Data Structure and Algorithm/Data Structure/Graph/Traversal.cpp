#include <iostream>
using namespace std;
// 定义标记变量
#define UNVISITED 0
#define VISITED 1

// 队列
template <typename T>
class Queue
{
private:
    T *data;      // 存储队列元素的数组
    int capacity; // 队列的容量
    int front;    // 队头指针
    int rear;     // 队尾指针
    int size;     // 队列的大小
public:
    // 构造函数
    Queue(int cap) : capacity(cap), front(0), rear(0), size(0)
    {
        data = new T[capacity]; // 动态分配数组
    }
    // 析构函数
    ~Queue()
    {
        delete[] data; // 释放数组内存
    }
    // 入队操作
    bool enqueue(T value)
    {
        if (isFull())
        {
            cout << "队列已满，无法入队！" << endl;
            return false;
        }
        data[rear] = value;           // 在队尾插入元素
        rear = (rear + 1) % capacity; // 更新队尾指针
        size++;                       // 队列大小加 1
        return true;
    }
    // 出队操作
    bool dequeue()
    {
        if (isEmpty())
        {
            cout << "队列为空，无法出队！" << endl;
            return false;
        }
        front = (front + 1) % capacity; // 更新队头指针
        size--;                         // 队列大小减 1
        return true;
    }
    // 获取队头元素
    T getFront() const
    {
        if (isEmpty())
        {
            throw runtime_error("队列为空，无法获取队头元素！");
        }
        return data[front]; // 返回队头元素
    }
    int length()
    {
        return size;
    }
};

// 图
class Graph
{
private:
    int numVertex;
    int numEdge;

public:
    void setMark(int v, bool mark) {} // 设置标记
    bool getMark(int v) {}            // 获取标记
    int first(int v) {}
    int next(int v, int w) {}
    int v() { return numEdge; }
    int n() { return numVertex; }
};

// 访问顶点的函数
void PreVisit(Graph *G, int v) {}
void PostVisit(Graph *G, int v) {}

// 深度优先遍历DFS
void DFS(Graph *G, int v)
{
    PreVisit(G, v); // 入栈时的对顶点操作
    G->setMark(v, VISITED);
    // 遍历v的所有邻居
    for (int w = G->first(v); w < G->n(); w = G->next(v, w))
    { // 该邻居未访问时 继续DFS
        if (G->getMark(w) == UNVISITED)
        {
            DFS(G, w);
        }
    }
    PostVisit(G, v); // 出栈时的对顶点操作
}

// 广度优先遍历BFS
void BFS(Graph *G, int start, Queue<int> *Q) // start为起始顶点
{
    int v, w;
    PreVisit(G, start);      // 入队时的对顶点操作
    G->setMark(start,VISITED);
    Q->enqueue(start);       // 入队
    while (Q->length() != 0) // 队列为空 BFS遍历结束
    {
        // 取出队列头的元素 遍历它所有未访问的邻居
        v = Q->getFront();
        Q->dequeue();
        PreVisit(G, v); // 出队时的对顶点操作
        // 遍历邻居
        for (w = G->first(v); w < G->n(); w = G->next(v, w))
        {
            if (G->getMark(w) == UNVISITED)
            {
                PreVisit(G, w); // 入队时的对顶点操作
                G->setMark(w,VISITED);
                Q->enqueue(w);
            }
        }
    }
}


// 拓扑排序
void topsort(Graph *G, Queue<int> *Q)
{
    int *indgree = new int[G->n()]; // 定义每个顶点的入度数组
    int v, w;
    // 初始化入度数组
    for (v = 0; v < G->n(); v++)
    {
        indgree[v] = 0;
    }

    // 计算入度 访问每条边
    for (v = 0; v < G->n(); v++)
    { // 找v的边 对应的w的入度加1
        for (w = G->first(v); w < G->n(); w = G->next(v, w))
        {
            indgree[w]++;
        }
    }
    
    // 将0入度顶点入队
    for (v = 0; v < G->n(); v++)
    {
        if (indgree[v] == 0)
        {
            Q->enqueue(v);
        }
    }
    while (Q->length() != 0)
    {
        v = Q->getFront();
        Q->dequeue();
        printout(v);

        //更新入度
        for (w = G->first(v); w < G->n();w=G->next(v,w))
        {
            indgree[w]--;
            if(indgree[w]==0)
            {
                Q->enqueue(w);
            }
        }
    }
}
// 打印函数
void printout(int v)
{
    cout << v;
}