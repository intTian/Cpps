#include <iostream>
using namespace std;
template <class Elem>
class List
{
public:
    virtual bool setPos(int pos) = 0;
    virtual bool insert(const Elem &e) = 0;
    virtual bool remove(Elem &e) = 0;
    virtual bool getValue(Elem &e) const = 0;
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
            length++;
            return true;
        }
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
    // 将栅栏移到首位
    bool setStart()
    {
        fence = head;
    }
    // 将栅栏移动到下一位
    void next()
    {
        if (curr != tail)
        {
            curr = curr->next;
        }
    }
};

// 定义标记变量
#define UNVISITED 0
#define VISITED 1

// ADT
class Graph
{
private:
    void operator=(const Graph &) {}
    Graph(const Graph &) {}

public:
    Graph() {};
    virtual ~Graph() {}

    // 初始化
    virtual void Init(int n) = 0;

    virtual int n() = 0; // 顶点数
    virtual int e() = 0; // 边数

    // v的第一个邻居
    virtual int first(int v) = 0;
    // v的w的下一个邻居
    virtual int next(int v, int w) = 0;

    // 设置边 v1到v2 权重
    virtual void setEdge(int v1, int v2, int wght) = 0;
    // 删除边
    virtual void delEdge(int v1, int v2) = 0;
};

// 邻接矩阵实现
class Graphm : public Graph
{
private:
    int **matrix;           // 动态二维数组 指向邻接矩阵
    int *mark;              // 指向标记数组 UNVISITED=0 VISITED=1
    int numVertex, numEdge; // 顶点数 边数
public:
    Graphm(int numVert)
    {
        int i, j;
        numVertex = numVert;
        numEdge = 0;
        mark = new int[numVert]; // 初始化标记数组
        for (int i = 0; i < numVertex; i++)
        {
            mark[i] = UNVISITED;
        }
        // 分配空间
        matrix = new int *[numVertex];
        for (i = 0; i < numVertex; i++)
        {
            matrix[i] = new int[numVertex];
        }
        // 初始化
        for (i = 0; i < numVertex; i++)
        {
            for (j = 0; j < numVertex; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    // 按照序号从小到大
    int first(int v)
    {
        int i;
        for (i = 0; i < numVertex; i++)
        {
            if (matrix[v][i] != 0)
            {
                return i;
            }
            return -1; // 没有找到
        }
    }
    int next(int v1, int v2)
    {
        int i;
        for (i = v2 + 1; i < numVertex; i++)
        {
            if (matrix[v1][i] != 0)
            {
                return i;
            }
            return -1;
        }
    }
};

// 邻接表实现
class Edge
{
public:
    int vertex, weight;
    Edge(int v, int w)
    {
        vertex = v;
        weight = w;
    }
    Edge() {}
};
class Graphl : public Graph
{
private:
    LList<Edge> **graph; // 链表头结点们（边的起点）
    int *mark;           // 标记数组
    int numVertex, numEdge;

public:
    Graphl(int numVert)
    {
        int i, j;
        numVertex = numVert;
        numEdge = 0;

        mark = new int[numVert];
        for (i = 0; i < numVertex; i++)
        {
            mark[i] = UNVISITED;
        }
        graph = new LList<Edge> *[numVertex];
        for (i = 0; i < numVertex; i++)
        {
            graph[i] = new LList<Edge>();
        }
    }
    int first(int v)
    {
        Edge it;
        graph[v]->setStart();
        if (graph[v]->getValue(it))
        {
            return it.vertex;
        }
        else
        {
            return -1;
        }
    }
    int next(int v1, int v2)
    {
        Edge it;
        graph[v1]->getValue(it); // getvalue为当前结点 提取当前结点的边为it
        if (it.vertex == v2)
        {
            graph[v1]->next(); // 移动栅栏
        }
        else // 从头开始找
        {
            graph[v1]->setStart();
            while (graph[v1]->getValue(it) && (it.vertex <= v2))
            {
                graph[v1]->next();
            }
        }
        if (graph[v1]->getValue(it))//找到了 否则栅栏在末端 为false
        {
            return it.vertex;
        }
        else
        {
            return -1;
        }
    }
};