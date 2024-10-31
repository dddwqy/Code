#include<iostream>
using namespace std;

int answer[10000];
int top;

template<class T>//线性表的类
class linearlist
{
public:
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual T& get(int index) = 0;
    virtual void indexof(const T& temp) = 0;
    virtual void insert(int inx, T element) = 0;
    virtual void erase(T val) = 0;
    virtual void output() = 0;
};

template<class T>//链表节点的类
class chainnode
{
public:
    chainnode() {}
    chainnode(T melement, chainnode<T>* m_next = NULL) :element(melement), next(m_next) {}//为每个节点设置索引
    T element;
    chainnode<T>* next;
};
//------------------------------------------------------------------------------------------------------------------------------------------------------------
template<class T>//链表类
class chain :public linearlist<T>
{
public:
    class iterator//这是一个链表内部实现迭代器的内部类
    {
    public:
        iterator(chainnode<T>* n = NULL) { node = n; }

        T& operator*() const { return node->element; }
        T* operator->() const { return  &node->element; }

        bool operator!=(const iterator right) const { return node != right.node; }
        bool operator==(const iterator right) const { return node == right.node; }

        iterator& operator++() { node = node->next; return *this; }
        iterator operator++(int) { iterator temp = *this; node = node->next; return temp; }
    protected:
        chainnode<T>* node;
    };

    chain(int initcapity = 10)
    {
        if (initcapity < 1)
        {
            cout << "error initcapity" << endl;
        }
        else {
            listsize = 0;
            firstnode =NULL;
        }
    }

    chain(const chain<T>& other_chain)//复制构造函数
    {
        listsize = other_chain.listsize;

        chainnode<T>* sourcenode = other_chain.firstnode;
        firstnode = new chainnode<T>(sourcenode->element);
        chainnode<T>* tagnode = firstnode;

        sourcenode = sourcenode->next;

        while (sourcenode != NULL)
        {
            tagnode->next = new chainnode<T>(sourcenode->element);
            tagnode = tagnode->next;
            sourcenode = sourcenode->next;
        }
        tagnode->next = NULL;
    }
    iterator begin() { return iterator(firstnode); }
    iterator end() { return iterator(); }
    bool empty() override { return listsize == 0; }//
    int size() override { return listsize; }//
    T& get(int index) override;
    void indexof(const T& temp) override;//
    void insert(int inx, T element) override;//
    void erase(T val) override;
    void output() override;
    void reverse();
    void operation(int i);
private:
    chainnode<T>* search();
    int listsize;
    chainnode<T>* firstnode;
};

template<class T>//返回该节点对应的索引
void chain<T>::indexof(const T& temp)
{
    chainnode<T>* source = firstnode;
    int index = 0;

    while (source!=NULL&&source->element != temp)
    {
        source = source->next;
        index++;
        //cout<<"是循环" << endl;
    }
    //cout<<"exit" << endl;
    if (source == NULL)
    {
        //cout<<"进入没有找到的分支" << endl;
        answer[top] = -1;
        top++;
    }
    else {
        answer[top] = index;
        //cout<<"进来了 :" <<top<<' '<< index << endl;
        top++;
    }
    return;
}

template<class T>
void chain<T>::insert(int inx, T element)
{
    if (inx<0 || inx>listsize)
    {
        cout << "error is insert's inx" << endl;
        return;
    }
    else {
        if (inx == 0)//当需要插入的地方为头节点时
        {
            chainnode<T>* new_first = new chainnode<T>(element, firstnode);
            firstnode = new_first;
            new_first = NULL;
        }
        else {//当需要插入的地方不是头节点时
            chainnode<T>* p = firstnode;
            for (int i = 0; i < inx - 1; i++)
            {
                p = p->next;
            }
            chainnode<T>* new_node = new chainnode<T>(element, p->next);
            p->next = new_node;
        }
        listsize++;
    }
    return;
}

template<class T>
void chain<T>::erase(T val)
{
    chainnode<T>* forward_node = firstnode;
    chainnode<T>* node = firstnode->next;

    if (forward_node->element == val)
    {
        firstnode = firstnode->next;
        delete forward_node;
        listsize--;
        return;
    }

    while (node != NULL)
    {
        if (node->element == val)
        {
            forward_node->next = node->next;
            delete node;
            listsize--;
            return;
        }
        forward_node = forward_node->next;
        node = node->next;
    }

    answer[top] = -1;
    top++;
    return;
}

template<class T>
chainnode<T>* chain<T>::search()//找到最后一个元素的位置
{
    chainnode<T>* answernode = firstnode;
    if (listsize == 0)
    {
        cout << "error is search:" << "0 " << endl;
    }
    else
    {
        for (int i = 0; i < listsize - 1; i++)
        {
            answernode = answernode->next;
        }
    }

    return answernode;
}

template<class T>
T& chain<T>::get(int index)
{
    chainnode<T>* node = firstnode;
    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }
    return node->element;
}

template<class T>
void chain<T>::output()//输出异或值
{
    int out = 0;
    int index = 0;
    iterator temp = begin();
    iterator temp_end = end();

    for (temp; temp != temp_end; temp++)
    {
        out += index ^ (*temp);
        index++;
    }
    answer[top] = out;
    top++;
}

template<class T>
void chain<T>::reverse()//这是一个将链表倒置的函数
{
    chainnode<T>* p1 = NULL, *p2 = NULL, *p3 = NULL;
    p1 = firstnode;
    p2 = p1->next;
    while (p2!=NULL)
    {
        p3 = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = p3;
    }
    firstnode->next = NULL;
    firstnode = p1;
    return;
}

template<class T>
void chain<T>::operation(int i)
{
    if (i == 1)
    {
        long index;
        T element;
        cin >> index >> element;
        insert(index, element);
    }
    else if (i == 2)
    {
        T val;
        cin >> val;
        erase(val);
    }
    else if (i == 3)
    {
        reverse();
    }
    else if (i == 4)
    {
        T val;
        cin >> val;
        indexof(val);
    }
    else if (i == 5)
    {
        output();
    }
    return;
}

int main()
{
    return 0;
}

