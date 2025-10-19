#include<iostream>
using namespace std;

// 二叉检索树
template <class Elem>
class BST
{
private:
    BinNode<Elem> *root;

public:

    // 查找 O(logn)
    bool find(BinNode<Elem> *root, Elem &e)
    {
        if (root == NULL)
            return false;
        else if (e < root->val)
            return find(root->lc, e);
        else if (e > root->val)
            return find(root->rc, e);
        else // 相等
            return true;
    }

    // 插入O(logn)
    BinNode<Elem> *insert(BinNode<Elem> *root, const Elem &e)
    {
        if (root == NULL)
        {
            return new BinNode<Elem>(e, NULL, NULL);
        }
        if (e < root->val)
        {
            root->lc = insert(root->lc, e);
        }
        else
        {
            root->rc = insert(root->rc, e);
        }
        return root;
    }

    // 删除
    void remove(Elem value)
    {
        root = removeHelper(root, value);
    }

    // 递归删除节点
    BinNode<Elem> *removeHelper(BinNode<Elem> *node, Elem value)
    {
        if (node == nullptr)
        {
            return nullptr; // 未找到节点
        }
        // 查找节点
        if (value < node->data)
        {
            node->left = removeHelper(node->left, value); // 在左子树中删除
        }
        else if (value > node->data)
        {
            node->right = removeHelper(node->right, value); // 在右子树中删除
        }
        else
        {
            // 找到要删除的节点
            if (node->left == nullptr && node->right == nullptr) // 情况 1: 叶子节点 删除即可
            {
                delete node;
                node = nullptr;
            }

            else if (node->left == nullptr) // 情况 2: 只有一个子节点  该结点的位置变成它之前的唯一子节点 只有右子结点 则将右子节点变为node
            {
                BinNode<Elem> *temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr)
            {
                BinNode<Elem> *temp = node;
                node = node->left;
                delete temp;
            }
            else // 情况 3: 有两个子节点
            {
                // 找到右子树中的最小节点 然后替换
                BinNode<Elem> *minRight = findMin(node->right);
                node->data = minRight->data;                             // 用最小节点的值替换当前节点的值
                node->right = removeHelper(node->right, minRight->data); // 删除最小节点
            }
        }
        return node;
    }
    // 查找最小节点（用于情况 3）
    BinNode<Elem> *findMin(BinNode<Elem> *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // 递归销毁树
    void destroyTree(BinNode<Elem> *node)
    {
        if (node == nullptr)
            return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
};