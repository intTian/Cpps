#include <iostream>
#include <vector>
using namespace std;
const int ORDER = 4; // B+树的阶数

template <class Key, class Value>
class BPTree
{
private:
    // 内部节点
    struct InternalNode
    {
        vector<Key> keys;        // 键
        vector<void *> children; // 子节点指针
        bool isLeaf;             // 是否为叶子节点

        InternalNode() : isLeaf(false) {}
    };

    // 叶子节点
    struct LeafNode
    {
        vector<Key> keys;     // 键
        vector<Value> values; // 值
        LeafNode *next;       // 指向下一个叶子节点

        LeafNode() : next(nullptr) {}
    };

    // 根节点
    void *root;

    // 插入辅助函数
    void insertInternal(InternalNode *node, const Key &key, void *child);
    void splitInternal(InternalNode *node, InternalNode *&newNode, Key &upKey);
    void insertLeaf(LeafNode *node, const Key &key, const Value &value);
    void splitLeaf(LeafNode *node, LeafNode *&newNode, Key &upKey);

    // 删除辅助函数
    void deleteInternal(InternalNode *node, const Key &key);
    void mergeInternal(InternalNode *parent, int index);
    void deleteLeaf(LeafNode *node, const Key &key);
    void mergeLeaf(LeafNode *parent, int index);

public:
    BPTree() : root(nullptr) {}

    // 插入接口
    void insert(const Key &key, const Value &value);

    // 删除接口
    void remove(const Key &key);

    // 查找接口
    Value search(const Key &key);

    // 打印树（辅助函数）
    void printTree();
};

// 插入
template <class Key, class Value>
void BPTree<Key, Value>::insert(const Key &key, const Value &value)
{
    if (root == nullptr)
    {
        // 空树，创建叶子节点
        LeafNode *leaf = new LeafNode();
        leaf->keys.push_back(key);
        leaf->values.push_back(value);
        root = leaf;
        return;
    }

    if (static_cast<LeafNode *>(root)->isLeaf)
    {
        // 根节点是叶子节点
        LeafNode *leaf = static_cast<LeafNode *>(root);
        insertLeaf(leaf, key, value);
    }
    else
    {
        // 根节点是内部节点
        InternalNode *node = static_cast<InternalNode *>(root);
        insertInternal(node, key, nullptr);
    }
}
template <class Key, class Value>
void BPTree<Key, Value>::insertLeaf(LeafNode *node, const Key &key, const Value &value)
{
    // 找到插入位置
    auto it = lower_bound(node->keys.begin(), node->keys.end(), key);
    int index = it - node->keys.begin();

    // 插入键和值
    node->keys.insert(it, key);
    node->values.insert(node->values.begin() + index, value);

    // 检查是否需要分裂
    if (node->keys.size() > ORDER)
    {
        LeafNode *newNode = new LeafNode();
        Key upKey;
        splitLeaf(node, newNode, upKey);

        if (root == node)
        {
            // 根节点分裂，创建新的根节点
            InternalNode *newRoot = new InternalNode();
            newRoot->keys.push_back(upKey);
            newRoot->children.push_back(node);
            newRoot->children.push_back(newNode);
            root = newRoot;
        }
    }
}
template <class Key, class Value>
void BPTree<Key, Value>::splitLeaf(LeafNode *node, LeafNode *&newNode, Key &upKey)
{
    // 分裂叶子节点
    int mid = node->keys.size() / 2;
    newNode->keys.assign(node->keys.begin() + mid, node->keys.end());
    newNode->values.assign(node->values.begin() + mid, node->values.end());
    node->keys.erase(node->keys.begin() + mid, node->keys.end());
    node->values.erase(node->values.begin() + mid, node->values.end());

    // 设置下一个叶子节点
    newNode->next = node->next;
    node->next = newNode;

    // 提升的键
    upKey = newNode->keys[0];
}

// 删除
template <class Key, class Value>
void BPTree<Key, Value>::remove(const Key &key)
{
    if (root == nullptr)
    {
        return;
    }

    if (static_cast<LeafNode *>(root)->isLeaf)
    {
        // 根节点是叶子节点
        LeafNode *leaf = static_cast<LeafNode *>(root);
        deleteLeaf(leaf, key);
    }
    else
    {
        // 根节点是内部节点
        InternalNode *node = static_cast<InternalNode *>(root);
        deleteInternal(node, key);
    }
}
template <class Key, class Value>
void BPTree<Key, Value>::deleteLeaf(LeafNode *node, const Key &key)
{
    // 找到删除位置
    auto it = lower_bound(node->keys.begin(), node->keys.end(), key);
    if (it == node->keys.end() || *it != key)
    {
        return; // 键不存在
    }

    // 删除键和值
    int index = it - node->keys.begin();
    node->keys.erase(it);
    node->values.erase(node->values.begin() + index);

    // 检查是否需要合并
    if (node->keys.size() < (ORDER + 1) / 2)
    {
        // TODO: 合并叶子节点
    }
}

// 查询
template <class Key, class Value>
Value BPTree<Key, Value>::search(const Key &key)
{
    if (root == nullptr)
    {
        return Value(); // 空树
    }

    void *node = root;
    while (!static_cast<LeafNode *>(node)->isLeaf)
    {
        InternalNode *internalNode = static_cast<InternalNode *>(node);
        auto it = lower_bound(internalNode->keys.begin(), internalNode->keys.end(), key);
        int index = it - internalNode->keys.begin();
        node = internalNode->children[index];
    }

    LeafNode *leafNode = static_cast<LeafNode *>(node);
    auto it = lower_bound(leafNode->keys.begin(), leafNode->keys.end(), key);
    if (it != leafNode->keys.end() && *it == key)
    {
        return leafNode->values[it - leafNode->keys.begin()];
    }
    return Value(); // 键不存在
}
