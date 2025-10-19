#include <iostream>
#include <vector>
using namespace std;
// 基于父指针数组的实现
class ParPtrTree
{
private:
    vector<int> parent; // 父指针数组
    vector<int> data;   // 节点数据

public:
    // 插入节点
    void insert(int value, int parentIndex)
    {
        data.push_back(value);
        parent.push_back(parentIndex);
    }

    // 获取父节点
    int getParent(int index)
    {
        if (index < 0 || index >= parent.size())
            return -1; // 无效索引
        return parent[index];
    }

    // 获取根节点
    int getRoot()
    {
        for (int i = 0; i < parent.size(); i++)
        {
            if (parent[i] == -1)
                return i;
        }
        return -1; // 没有根节点
    }

    // 打印树
    void printTree()
    {
        cout << "Node\tData\tParent" << endl;
        for (int i = 0; i < data.size(); i++)
        {
            cout << i << "\t" << data[i] << "\t" << parent[i] << endl;
        }
    }
};

// 基于链接的左孩子右兄弟结点表示法的实现
struct TreeNode
{
    int data;
    TreeNode *leftChild;    // 左孩子
    TreeNode *rightSibling; // 右兄弟

    // 构造函数
    TreeNode(int value) : data(value), leftChild(nullptr), rightSibling(nullptr) {}
};
class ChildSiblingTree
{
private:
    TreeNode *root; // 根节点

    // 递归销毁树
    void destroyTree(TreeNode *node)
    {
        if (node == nullptr)
            return;
        destroyTree(node->leftChild);
        destroyTree(node->rightSibling);
        delete node;
    }

    // 递归打印树
    void printTree(TreeNode *node, int level)
    {
        if (node == nullptr)
            return;

        // 打印当前节点
        for (int i = 0; i < level; i++)
            cout << "  ";
        cout << node->data << endl;

        // 递归打印左孩子和右兄弟
        printTree(node->leftChild, level + 1);
        printTree(node->rightSibling, level);
    }

public:
    // 构造函数
    ChildSiblingTree() : root(nullptr) {}

    // 析构函数
    ~ChildSiblingTree()
    {
        destroyTree(root);
    }

    // 插入节点
    void insert(int parentValue, int value)
    {
        TreeNode *newNode = new TreeNode(value);

        if (root == nullptr)
        {
            root = newNode;
            return;
        }

        // 查找父节点
        TreeNode *parent = findNode(root, parentValue);
        if (parent == nullptr)
        {
            cout << "Parent not found!" << endl;
            return;
        }

        // 插入为左孩子或右兄弟
        if (parent->leftChild == nullptr)
        {
            parent->leftChild = newNode;
        }
        else
        {
            TreeNode *sibling = parent->leftChild;
            while (sibling->rightSibling != nullptr)
            {
                sibling = sibling->rightSibling;
            }
            sibling->rightSibling = newNode;
        }
    }

    // 查找节点
    TreeNode *findNode(TreeNode *node, int value)
    {
        if (node == nullptr)
            return nullptr;
        if (node->data == value)
            return node;

        TreeNode *found = findNode(node->leftChild, value);
        if (found != nullptr)
            return found;

        return findNode(node->rightSibling, value);
    }

    // 打印树
    void printTree()
    {
        printTree(root, 0);
    }
};
