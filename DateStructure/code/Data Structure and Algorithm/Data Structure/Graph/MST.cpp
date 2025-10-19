#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 定义标记变量
#define UNVISITED 0
#define VISITED 1
#define INFINITYT INT_MAX

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
    int weight(int v, int w) {}
};

// Prim算法
void Prim(Graph *G, int *D, int s)
{
    // D[v] 表示从当前生成树到顶点 v 的最小权重。int s：起始顶点 任意
    int V[G->n()]; // 存储距离选择的部分最近的顶点 V[v] 表示顶点 v 在生成树中的父节点。
    int i, w;

    // 初始化 D 数组
    for (i = 0; i < G->n(); i++)
    {
        D[i] = INFINITYT;
        V[i] = -1; // 初始时没有父节点
    }
    D[s] = 0;

    // n步 每步找一个点
    for (i = 0; i < G->n(); i++)
    {
        // 找最小权重 未访问的点 然后标记访问
        int v = minVertex(G, D);
        G->setMark(v, VISITED);

        // 加入边到MST
        if (v != s)
        {
            AddEdgetoMST(V[v], v);
        }

        // 图不连通
        if (D[v] == INFINITYT)
        {
            return;
        }

        // 更新值 将v的所有邻居的边的权重与之前的比较 如果权重更小则更新值和父节点
        for (w = G->first(v); w < G->n(); w = G->next(v, w))
        {
            if (D[w] > G->weight(v, w))
            {
                D[w] = G->weight(v, w);
                V[w] = v;
            }
        }
    }
}
// 加入边到MST
void AddEdgetoMST(int V, int v) {}
// 在数组D中选择最小且未访问的顶点v
int minVertex(Graph *G, int *D)
{
    // 初始化
    int i, v;
    int min = INFINITYT;

    // 遍历
    for (i = 0; i < G->n(); i++)
    {
        if (G->getMark(i) == UNVISITED & D[i] < min)
        {
            // 更新值
            v = i;
            min = D[i];
        }
    }
}

// Kruskal 算法
void Kruskal(Graph *G)
{
    ParPtrTree A(G->n());    // 初始化并查集
    vector<KruskElem> edges; // 存储所有边

    // 收集所有边
    for (int i = 0; i < G->n(); i++)
    {
        for (int w = G->first(i); w != -1; w = G->next(i, w))
        {
            edges.push_back(KruskElem(i, w, G->weight(i, w)));
        }
    }

    // 构建最小堆
    heap<KruskElem, less<KruskElem>> H(edges.data(), edges.size(), edges.size());

    int numMST = G->n(); // 初始化等价对
    while (numMST > 1)
    {
        KruskElem temp = H.removefirst(); // 取出最小边
        int v = temp.from;
        int u = temp.to;

        // 如果边的两个顶点不在同一个集合中，则加入生成树
        if (A.differ(v, u))
        {
            A.UNION(v, u);
            cout << "Add edge: " << v << " -- " << u << " : " << temp.distance << endl;
            numMST--;
        }
    }
}
// 并查集（用于检测环）
class ParPtrTree
{
private:
    vector<int> parent; // 父节点数组
    vector<int> rank;   // 秩数组（用于优化合并操作）

public:
    ParPtrTree(int n)
    {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // 初始时每个节点的父节点是自身
            rank[i] = 0;   // 初始时每个集合的秩为 0
        }
    }

    // 查找根节点（带路径压缩）
    int FIND(int x)
    {
        if (x != parent[x])
        {
            parent[x] = FIND(parent[x]); // 路径压缩
        }
        return parent[x];
    }

    // 合并两个集合（按秩合并）
    void UNION(int x, int y)
    {
        int rootX = FIND(x);
        int rootY = FIND(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    // 判断两个节点是否属于同一个集合
    bool differ(int x, int y)
    {
        return FIND(x) != FIND(y);
    }
};
// 边的结构体
class KruskElem
{
public:
    int from, to, distance; // 边的起点、终点和权重

    KruskElem() : from(-1), to(-1), distance(-1) {}
    KruskElem(int f, int t, int d) : from(f), to(t), distance(d) {}

    // 重载小于运算符，用于堆排序
    bool operator<(const KruskElem &other) const
    {
        return distance < other.distance;
    }
};
// 最小堆的实现
template <typename T, typename Comp>
class heap
{
private:
    vector<T> data;
    Comp comp;

public:
    heap(T *array, int size, int maxSize)
    {
        data.assign(array, array + size);
        make_heap(data.begin(), data.end(), comp);
    }

    // 移除堆顶元素
    T removefirst()
    {
        pop_heap(data.begin(), data.end(), comp);
        T result = data.back();
        data.pop_back();
        return result;
    }
};

