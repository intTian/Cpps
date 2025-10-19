// 栈
// ADT
template <class Elem>
class Stack
{
public:
    virtual bool push(const Elem &e) = 0;
    virtual bool pop(Elem &e) = 0;
    virtual bool topValue(Elem &e) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
};
// 基于顺序表的栈
template <class Elem>
class AStack : public Stack<Elem>
{
private:
    Elem *listArray;
    int size;
    int top; // index for  new top element

public:
    AStack(int sz)
    {
        size = sz;
        top = 0;
        listArray = new Elem[sz];
    }
    ~AStack()
    {
        delete[] listArray;
    }
    bool push(const Elem &item)
    {
        if (top == size) // 栈满
        {
            return false;
        }
        else
        {
            listArray[top++] = item;
            return true;
        }
    }
    bool pop(Elem &it)
    {
        if (top == 0) // 无元素
        {
            return false;
        }
        else
        {
            it = listArray[--top];
            return true;
        }
    }
};

// 基于链表的栈
template <typename T>
class LStack
{
private:
    Node<T> *top; // 栈顶指针
    int size;     // 栈的大小

public:
    // 构造函数
    LStack() : top(nullptr), size(0) {}

    // 析构函数
    ~LStack()
    {
        clear(); // 销毁栈
    }

    // 入栈操作
    void push(T value)
    {
        Node<T> *newNode = new Node<T>(value); // 创建新节点
        newNode->next = top;                   // 新节点指向当前栈顶
        top = newNode;                         // 更新栈顶指针
        size++;                                // 栈大小加 1
    }

    // 出栈操作
    bool pop()
    {
        if (isEmpty())
        {
            cout << "栈为空，无法出栈！" << endl;
            return false;
        }
        Node<T> *temp = top; // 保存当前栈顶
        top = top->next;     // 更新栈顶指针
        delete temp;         // 释放原栈顶节点
        size--;              // 栈大小减 1
        return true;
    }

    // 获取栈顶元素
    T getTop() const
    {
        if (isEmpty())
        {
            throw runtime_error("栈为空，无法获取栈顶元素！");
        }
        return top->data; // 返回栈顶元素
    }
};
