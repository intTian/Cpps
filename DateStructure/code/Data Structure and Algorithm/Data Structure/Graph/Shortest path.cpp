#include <iostream>
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

// Dijkstra
// 计算最短路径问题 单源最短路径 原点为s 返回距离为数组D
void Dijkstra(Graph *G, int *D, int s)
{
    // 初始化
    int i = 0, v, w;
    for (i = 0; i < G->n(); i++)
    {
        D[i] = INFINITYT;
    }
    D[s] = 0;

    for (i = 0; i < G->n(); i++)
    {
        // 在数组D中选择最小且未访问的顶点v
        v = minVertex(G, D);
        // 标记v
        G->setMark(v, VISITED);
        // 更新值
        for (w = G->first(v); w < G->n(); w = G->next(v, w))
        {
            if (D[v] + G->weight(v, w) < D[w])
            {
                D[w] = D[v] + G->weight(v, w);
            }
        }
    }
}

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