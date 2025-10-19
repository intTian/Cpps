#include <iostream>
using namespace std;

// 基于链接的二叉树
template <class Elem>
class BinNode
{
public:
    Elem val;
    BinNode *lc;
    BinNode *rc;
    BinNode(Elem e, BinNode *l, BinNode *r) { val = e, lc = l, rc = r; }
};
template <class Elem>
class LBinTree
{
private:
    BinNode<Elem> *root;

public:
    void preorder(BinNode<Elem> *root) // 前序遍历 根 左 右
    {
        if (root == NULL)
            return;

        // cout << root; some action to root

        preorder(root->lc);

        preorder(root->rc);
    }
    void postorder(BinNode<Elem> *root) // 后序遍历 左 右 根
    {
        if (root == NULL)
            return;
        postorder(root->lc);

        postorder(root->rc);

        // cout << root; some action to root
    }
    void inorder(BinNode<Elem> *root) // 中序遍历 左 根 右
    {
        if (root == NULL)
            return;
        inorder(root->lc);

        // cout << root; some action to root

        inorder(root->rc);
    }
};

// 基于数组的二叉树
template <typename T>
class ABinTree
{
private:
    vector<T> tree; // 存储二叉树的数组
public:
    // 构造函数
    ABinTree(int capacity = 100)
    {
        tree.resize(capacity, T()); // 初始化数组，默认容量为 100
    }

    // 插入根节点
    void setRoot(T value)
    {
        if (tree.empty())
        {
            tree.push_back(value); // 在索引 0 处插入根节点
        }
        else
        {
            tree[0] = value; // 更新根节点
        }
    }
    // 插入左子节点
    void setLeftChild(int parentIndex, T value)
    {
        if (parentIndex < 0 || parentIndex >= tree.size())
        {
            throw out_of_range("父节点索引越界！");
        }
        int leftChildIndex = 2 * parentIndex + 1;
        if (leftChildIndex >= tree.size())
        {
            tree.resize(leftChildIndex + 1, T()); // 动态扩展数组
        }
        tree[leftChildIndex] = value; // 插入左子节点
    }

    // 插入右子节点
    void setRightChild(int parentIndex, T value)
    {
        if (parentIndex < 0 || parentIndex >= tree.size())
        {
            throw out_of_range("父节点索引越界！");
        }
        int rightChildIndex = 2 * parentIndex + 2;
        if (rightChildIndex >= tree.size())
        {
            tree.resize(rightChildIndex + 1, T()); // 动态扩展数组
        }
        tree[rightChildIndex] = value; // 插入右子节点
    }

    // 获取节点值
    T getValue(int index) const
    {
        if (index < 0 || index >= tree.size())
        {
            throw out_of_range("节点索引越界！");
        }
        return tree[index];
    }

    // 获取左子节点索引
    int getLeftChildIndex(int parentIndex) const
    {
        if (parentIndex < 0 || parentIndex >= tree.size())
        {
            throw out_of_range("父节点索引越界！");
        }
        int leftChildIndex = 2 * parentIndex + 1;
        if (leftChildIndex >= tree.size() || tree[leftChildIndex] == T())
        {
            return -1; // 左子节点不存在
        }
        return leftChildIndex;
    }

    // 获取右子节点索引
    int getRightChildIndex(int parentIndex) const
    {
        if (parentIndex < 0 || parentIndex >= tree.size())
        {
            throw out_of_range("父节点索引越界！");
        }
        int rightChildIndex = 2 * parentIndex + 2;
        if (rightChildIndex >= tree.size() || tree[rightChildIndex] == T())
        {
            return -1; // 右子节点不存在
        }
        return rightChildIndex;
    }

    // 获取父节点索引
    int getParentIndex(int childIndex) const
    {
        if (childIndex <= 0 || childIndex >= tree.size())
        {
            return -1; // 父节点不存在
        }
        return (childIndex - 1) / 2;
    }
};



