template <class Elem>
class Queue
{
public:
    virtual bool enqueue(const Elem &e) = 0;
    virtual bool dequeue(Elem &e) = 0;
    virtual bool frontValue(Elem &e) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
};

// 基于顺序表的队列
template <typename T>
class Queue
{
private:
    T *data;      // 存储队列元素的数组
    int capacity; // 队列的容量
    int front;    // 队头指针
    int rear;     // 队尾指针
    int size;     // 队列的大小

public:
    // 构造函数
    Queue(int cap) : capacity(cap), front(0), rear(0), size(0)
    {
        data = new T[capacity]; // 动态分配数组
    }

    // 析构函数
    ~Queue()
    {
        delete[] data; // 释放数组内存
    }

    // 入队操作
    bool enqueue(T value)
    {
        if (isFull())
        {
            cout << "队列已满，无法入队！" << endl;
            return false;
        }
        data[rear] = value;           // 在队尾插入元素
        rear = (rear + 1) % capacity; // 更新队尾指针
        size++;                       // 队列大小加 1
        return true;
    }

    // 出队操作
    bool dequeue()
    {
        if (isEmpty())
        {
            cout << "队列为空，无法出队！" << endl;
            return false;
        }
        front = (front + 1) % capacity; // 更新队头指针
        size--;                         // 队列大小减 1
        return true;
    }

    // 获取队头元素
    T getFront() const
    {
        if (isEmpty())
        {
            throw runtime_error("队列为空，无法获取队头元素！");
        }
        return data[front]; // 返回队头元素
    }
};

// 基于链表的队列
template <typename T>
class Node
{
public:
    T data;     // 数据域
    Node *next; // 指针域

    // 构造函数
    Node(T value) : data(value), next(nullptr) {}
};
template <typename T>
class LQueue
{
private:
    Node<T> *front; // 队头指针
    Node<T> *rear;  // 队尾指针
    int size;       // 队列的大小

public:
    // 构造函数
    LQueue() : front(nullptr), rear(nullptr), size(0) {}

    // 析构函数
    ~LQueue()
    {
        clear(); // 销毁队列
    }

    // 入队操作
    void enqueue(T value)
    {
        Node<T> *newNode = new Node<T>(value); // 创建新节点
        if (isEmpty())
        {
            front = rear = newNode; // 队列为空时，新节点既是队头也是队尾
        }
        else
        {
            rear->next = newNode; // 将新节点链接到队尾
            rear = newNode;       // 更新队尾指针
        }
        size++; // 队列大小加 1
    }

    // 出队操作
    bool dequeue()
    {
        if (isEmpty())
        {
            cout << "队列为空，无法出队！" << endl;
            return false;
        }
        Node<T> *temp = front; // 保存当前队头
        front = front->next;   // 更新队头指针
        delete temp;           // 释放原队头节点
        if (front == nullptr)
        {
            rear = nullptr; // 如果队列为空，更新队尾指针
        }
        size--; // 队列大小减 1
        return true;
    }

    // 获取队头元素
    T getFront() const
    {
        if (isEmpty())
        {
            throw runtime_error("队列为空，无法获取队头元素！");
        }
        return front->data; // 返回队头元素
    }
    // 清空队列
    void clear()
    {
        while (!isEmpty())
        {
            dequeue(); // 逐个出队
        }
    }
};
