#include <iostream>
using namespace std;
#define EMPTYKEY -1
template <class Key, class Elem>
class TTNode
{
public:
    Key lkey;
    Elem le;
    Key rkey;
    Elem re;
    TTNode *left;
    TTNode *center;
    TTNode *right;
    TTNode(Key lk, Elem lv, Key rk, Elem rv, TTNode<Key, Elem> *p1, TTNode<Key, Elem> *p2, TTNode<Key, Elem> *p3)
    {
        lkey = lk;
        rkey = rk;
        le = lv;
        re = rv;
        left = p1;
        center = p2;
        right = p3;
    }
    bool isLeaf()
    {
        return left == NULL;
    }
};
template <class Key, class Elem>
class TTTree
{
private:
    TTNode<Key, Elem> *root;
};

// 查找 O(logn)
template <class Key, class Elem>
bool Search(TTNode<Key, Elem> *root, const Key &K, Elem &e)
{
    if (root == NULL)
    {
        return false;
    }
    if (K == root->lkey)
    {
        e = root->le;
        return true;
    }
    if (K == root->rkey)
    {
        e = root->re;
        return true;
    }
    if (K < root->lkey)
    {
        Search(root->left, K, e);
    }
    else if (root->right == NULL) // 只有两个子结点
    {
        return Search(root->center, K, e);
    }
    else if (K < root->rkey)
    {
        return Search(root->center, K, e);
    }
    else
    {
        return return Search(root->right, K, e);
    }
}

// 插入 O(logn)
template <class Key, class Elem>
TTNode<Key, Elem> *add(TTNode<Key, Elem> *it)
{
    if (rkey == EMPTYKEY) // 只有一个key，直接插入
    {
        if (lkey < it->lkey) // 插入到右边
        {
            // 更新被插入的结点情况
            rkey = it->lkey;
            re = it->le;
            right = center;
            center = it->center;
        }
        else // 插入到左边
        {
            rkey = lkey;
            re = le;
            right = center;
            lkey = it->lkey;
            le = it->le;
            center = it->center; // center为插入的center
        }
        return this;
    }
    else if (lkey >= it->lkey) // 插入左边
    {
        center = new TTNode<Key, Elem>(rkey, re, EMPTYKEY, NULL, center, right, NULL);
        rkey = EMPTYKEY;
        re = NULL;
        right = NULL;
        it->left = left;
        left = it;
        return this;
    }
    else if (rkey < it->lkey) // 插入中间
    {
        // 分裂中间
        TTNode<Key, Elem> *newNode = new TTNode<Key, Elem>(rkey, re, EMPTYKEY, NULL, it->center, right, NULL);
        rkey = EMPTYKEY;
        re = NULL;
        right = NULL;
        it->center = center;
        center = newNode;
        return this;
    }
    else // 插入右边
    {
        // 分裂右边
        TTNode<Key, Elem> *newNode = new TTNode<Key, Elem>(rkey, re, EMPTYKEY, NULL, right, it->center, NULL);
        rkey = EMPTYKEY;
        re = NULL;
        right = NULL;
        it->center = center;
        center = newNode;
        return this;
    }
}
template <class Key, class Elem>
TTNode<Key, Elem> *inserthelp(TTNode<Key, Elem> *rt, const Key k, const Elem e)
{
    TTNode<Key, Elem> *retval; // 返回的根节点
    if (rt == NULL)
    {
        return new TTNode<Key, Elem>(k, e, EMPTYKEY, NULL, NULL.NULL.NULL);
    }
    // 插入叶子结点
    if (rt->isLeaf())
    {
        return rt->add(new TTNode<Key, Elem>(k, e, EMPTYKEY, NULL, NULL.NULL.NULL))
    }
    // 插入内部结点
    if (k < rt->lkey)
    {
        retval = inserthelp(rt->left, k, e);
        if (retval == rt->left)
        {
            return rt;
        }
        else
        {
            return rt->add(retval);
        }
    }
    else if ((rt->rkey == EMPTYKEY) || (k < rt->rkey))
    {
        retval = inserthelp(rt->center, k, e) if (retval == rt->center)
        {
            return rt;
        }
        else
        {
            rt->add(retval);
        }
    }
    else
    {
        retval = inserthelp(rt->right, k, e);
        if (retval == rt->right)
        {
            return rt;
        }
        else
        {
            return rt->add(retval);
        }
    }
}
