#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 哈夫曼树节点类
struct HuffNode
{
    char data;       // 字符（如果是叶子节点）
    int freq;        // 频率
    HuffNode *left;  // 左子节点
    HuffNode *right; // 右子节点

    // 构造函数
    HuffNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// 比较器类（用于优先队列）
struct Compare
{
    bool operator()(HuffNode *a, HuffNode *b)
    {
        return a->freq > b->freq; // 频率小的优先级高
    }
};

class HuffTree
{
private:
    HuffNode *root; // 根节点

    // 递归生成哈夫曼编码
    void generateCodes(HuffNode *node, string code, unordered_map<char, string> &huffmanCode)
    {
        if (node == nullptr)
            return;

        // 如果是叶子节点，存储编码
        if (!node->left && !node->right)
        {
            huffmanCode[node->data] = code;
        }

        // 递归处理左子树和右子树
        generateCodes(node->left, code + "0", huffmanCode);
        generateCodes(node->right, code + "1", huffmanCode);
    }

    // 递归销毁树
    void destroyTree(HuffNode *node)
    {
        if (node == nullptr)
            return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    // 构造函数
    HuffTree() : root(nullptr) {}

    // 析构函数
    ~HuffTree()
    {
        destroyTree(root); // 销毁树
    }

    // 构建哈夫曼树
    void buildTree(const unordered_map<char, int> &freqMap)
    {
        // 优先队列（最小堆）
        priority_queue<HuffNode *, vector<HuffNode *>, Compare> minHeap;

        // 将所有字符及其频率插入最小堆
        for (auto &pair : freqMap)
        {
            minHeap.push(new HuffNode(pair.first, pair.second));
        }

        // 构建哈夫曼树
        while (minHeap.size() > 1)
        {
            // 取出频率最小的两个节点
            HuffNode *left = minHeap.top();
            minHeap.pop();
            HuffNode *right = minHeap.top();
            minHeap.pop();

            // 创建一个新节点，频率为两个子节点的频率和
            HuffNode *newNode = new HuffNode('\0', left->freq + right->freq);
            newNode->left = left;
            newNode->right = right;

            // 将新节点插入最小堆
            minHeap.push(newNode);
        }

        // 最后剩下的节点就是根节点
        root = minHeap.top();
    }

    // 生成哈夫曼编码
    unordered_map<char, string> generateCodes()
    {
        unordered_map<char, string> huffmanCode;
        generateCodes(root, "", huffmanCode);
        return huffmanCode;
    }

    // 打印哈夫曼编码
    void printCodes()
    {
        unordered_map<char, string> huffmanCode = generateCodes();
        for (auto &pair : huffmanCode)
        {
            cout << pair.first << ": " << pair.second << endl;
        }
    }
};
