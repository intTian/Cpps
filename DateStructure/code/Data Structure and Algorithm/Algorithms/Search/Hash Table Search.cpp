#include <iostream>
using namespace std;
// 直接定址法
int DirectHash(int key)
{
    return key;
}
// 取模法
int ModuloHash(int key, int m)
{
    return key % m;
}
// 平方取中法
int MidSquareHash(int key, int digits)
{
    long long squared = (long long)key * key;
    string squaredStr = to_string(squared);
    int len = squaredStr.length();
    int start = (len - digits) / 2;
    string midDigits = squaredStr.substr(start, digits);
    return stoi(midDigits);
}

// 对于字符串
// 求和取模法
int ModuloSumhash(char *x, int M)
{
    int i, sum;
    for (sum = 0, i = 0; x[i] != '\0'; i++)
    {
        sum += (int)x[i];
    }
    return sum % M;
}
// ELF
int ELFHash(char *key, int M)
{
    unsigned long h = 0;
    while (*key)
    {
        h = (h << 4) + *key++;
        unsigned long g = h & 0xF0000000L;
        if (g)
            h ^= g >> 24;
        h &= ~g;
    }
    return h % M;
}

// 字典ADT
template <typename Key, typename E>
class Dictionary
{
private:
    void operator=(const Dictionary &) {}
    Dictionary(const Dictionary &) {}

public:
    Dictionary() {}
    virtual ~Dictionary() {}
    // 重新初始化
    virtual void clear() = 0;
    // 插入一个记录
    virtual void insert(const Key &k, const E &e) = 0;
    // 移除的一个记录并返回
    virtual E remove(const Key &k) = 0;
    // 移除任意的记录并返回
    virtual E removeAny() = 0;
    virtual E find(const Key &k) const = 0;
    virtual int size() = 0;
};
// 键值对的实现
template <typename Key, typename E>
class KVpair
{
private:
    Key k;
    E e;

public:
    KVpair() {}
    KVpair(Key, kval, E eval)
    {
        k = kval;
        e = eval;
    }
    KVpair(const KVpair &o)
    {
        k = o.k;
        e = o.e;
    }
    void operator=(const KVpair &o)
    {
        k = o.k;
        e = o.e;
    }
    Key key() { return k; }
    void setKey(Key ink)
    {
        k = ink;
    }
    E value()
    {
        return e;
    }
};
// 哈希表的实现
template <typename Key, typename E>
class hashdict : public Dictionary<Key, E>
{
private:
    KVpair<Key, E> *HT; // 键值对数组 哈希表
    int M;              // 哈希表大小
    int current;        // 哈希表中储存的元素个数
    Key EMPTYKEY;
    int p(Key K, int i) const // 线性探测
    {
        return i;
    }
    int h(int key)
    {
        return key % M;
    }
    int h(char *x)
    {
        int i, sum;
        for (sum = 0, i = 0; x[i] != '\0'; i++)
        {
            sum += (int)x[i];
        }
        return sum % M;
    }
    // 插入
    bool hashInsert(const Key &k, const E &e)
    {
        int home = h(k); // 初始位置
        int pos = home;  // 初始化探测序列
        int i = 1;       // 初始化探测次数
        while (HT[pos].key() != EMPTYKEY)
        { // 当前位置已经有重复的关键字
            if (k == HT[pos].key())
            {
                return false;
            }
            // 尝试下个探测的位置
            pos = (home + p(k, i)) % M;
            i++;
        }
        // 找到一个空的位置 即pos
        KVpair<Key, E> temp(k, e);
        HT[pos] = temp;
        return true;
    }

    // 查找
    bool hashSearch(const Key &K, const E &e) const
    {
        int home = h(k);                                        // 初始位置
        int pos = home;                                         // 初始化探测序列
        int i = 1;                                              // 初始化探测次数
        while (HT[pos].key() != EMPTYKEY && K != HT[pos].key()) // 探测的位置不为空且不为k 则继续探测
        {
            pos = (home + p(K, i++)) % M; // 更新i
        }
        if (K == HT[pos].key()) // 找到
        {
            e = HT[pos];
            return true;
        }
        else
        {
            return false;
        }
    }

public:
    hashdict(int sz, Key k)
    {
        M = sz;
        EMPTYKEY = k;
        current = 0;
        HT = new KVpair<Key, E>[sz];]
        //初始化
        for (int i = 0; i < M;i++)
        {
            (HT[i].setKey(EMPTYKEY));
        }
        
    }
    ~hashdict()
    {
        delete HT;
    }

    // 插入
    bool insert(const Key &k, const E &it)
    {
        if (current >= M)
        {
            return false;
        }
        hashInsert(k, it);
        currcnt++;
        return true;
    }

    // 查找
    E find(const &Key k, const &E e) const
    {
        return hashSearch(k, e);
    }

    int size()
    {
        return sz;
    }
};
