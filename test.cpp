#include<iostream>
using namespace std;

int final_answer[10];
int top;

template<class T>//线性表的类
class linearlist
{
public:
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual T get(int index) = 0;
    virtual int indexof(const T& temp) = 0;
    virtual void insert(int inx, T element) = 0;
    virtual void erase(int index) = 0;
    //virtual int output() = 0;
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
            firstnode = NULL;
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

    ~chain()
    {
        if (listsize != 0)
        {
            while(firstnode!=NULL)
            {
              chainnode<T>*temp=firstnode;
              firstnode=firstnode->next;
              delete temp;
            }
        }

    }
    iterator begin() { return iterator(firstnode); }
    iterator end() { return iterator(); }
    bool empty() override { return listsize == 0; }//
    int size() override { return listsize; }//
    T get(int index) override;
    int indexof(const T& temp) override;//
    void insert(int inx, T element) override;//
    void erase(int index) override;
   // int output() override;
    //void reverse();
    //void operation(int i);
private:
    //chainnode<T>* search();
    int listsize;
    chainnode<T>* firstnode;
};

template<class T>//返回该节点对应的索引
int chain<T>::indexof(const T& temp)
{
    chainnode<T>* source = firstnode;
    int index = 0;

    while (source != NULL && source->element != temp)
    {
        source = source->next;
        index++;
        //cout<<"是循环" << endl;
    }
    //cout<<"exit" << endl;
    if (source == NULL)
    {
        //cout<<"进入没有找到的分支" << endl;
        return -1;
    }
    else {
        return index;
    }
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
void chain<T>::erase(int index)///这个地方出现问题
{
    chainnode<T>* forward_node = firstnode;
  
   if(listsize!=0&&index>=0&&index<listsize)
   {
     if (index == 0)
    {
        firstnode = firstnode->next;
        delete forward_node;
        listsize--;
        return;
    }

    for (int i = 0; i < index - 1; i++)
    {
        forward_node = forward_node->next;
    }
    chainnode<T>* deletenode = forward_node->next;
    forward_node->next = forward_node->next->next;
    delete deletenode;
    listsize--;
   }
    
    return;
}

template<class T>
T chain<T>::get(int index)
{
    chainnode<T>* node = firstnode;
    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }
    return node->element;
}


template<class T>
class merge_chain
{
public:
    merge_chain() {}
    int radix(T input, int n = 10, int c = 0);
    void radixsort(chain<T>& thechain, int n, int c);
    void boinsort(chain<T>& temp, int range, int num);//这个num表示是数字上的第几位数字
    void merge_two(chain<T>& chain_one, chain<T>& chain_two, int n, int c);
    void cal_xor(chain<T>& thechain);
    ~merge_chain() {}
private:
    chain<T> answer_head;//定义一个储存答案链表的链表头
};

template<class T>
int merge_chain<T>::radix(T input, int n, int c)
{
    int r1 = 1, r2 = 1;
    for (int i = 0; i < c; i++)
    {
        r1 *= n;
        r2 *= n;
    }
    r2 *= n;
    //cout<<"r1 :"<<r1<<endl;
    //cout<<"r2 :"<<r2<<endl;
    //cout<<(input%r2)/r1<<endl;
    return (input % r2) / r1;//返回一个该数位上的值
}

template<class T>
void merge_chain<T>::radixsort(chain<T>& thechain, int n, int c)
{
    for (int j = 0; j < c; j++)//这里用来控制数位
    {
        boinsort(thechain, n - 1, j);//如果进制是10的话，那么范围为0-9，所以n-1
    }
    return;
}

template<class T>
void merge_chain<T>::boinsort(chain<T>& temp, int range, int num)
{
    chain<T>* boin = new chain<T>[range + 1];
    int nr = temp.size();
    //cout<<"数位为 ："<<num<<endl;
    if (nr != 0)
    {
        for (int i = 0; i < nr; i++)
        {
            // cout<<"i = "<<i<<endl;
            T rec = temp.get(0);
            //cout<<rec<<endl;
            temp.erase(0);
            //cout<<radix(rec,range+1,num)<<endl;
            boin[radix(rec, range + 1, num)].insert(0, rec);
        }
        //cout<<"出来没"<<endl;

        for (int i = range; i >= 0; i--)
        {
            //cout<<"在while中:"<<i<<endl;
            while (!boin[i].empty())
            {
                //cout<<"现在的i为："<<i<<endl;
                //cout<<boin[i].size()<<endl;
                T rec = boin[i].get(0);
                //cout<<"rec为："<<rec<<endl;
                boin[i].erase(0);
                temp.insert(0, rec);
            }
            // cout<<boin[i].size()<<endl;
        }
    }
    delete[] boin;
    return;
}

template<class T>
void merge_chain<T>::cal_xor(chain<T>& thechain)
{
    typename chain<T>::iterator head = thechain.begin();
    typename chain<T>::iterator ends = thechain.end();
    int out = 0;
    int index = 0;

    while (head != ends)
    {
        out += index ^ (*head);
        index++;
        ++head;
    }

    final_answer[top] = out;
    top++;

    return;
}

template<class T>
void merge_chain<T>::merge_two(chain<T>& chain_one, chain<T>& chain_two, int n, int c)
{
    //cout<<"enter"<<endl;
    int answer = 0;
    radixsort(chain_one, n, c);//将两个链表进行基数排序
    radixsort(chain_two, n, c);
    cal_xor(chain_one);
    cal_xor(chain_two);

    int size_one = chain_one.size();
    int size_two = chain_two.size();
    int size_total = size_one + size_two;//answer地总长度

    typename chain<T>::iterator one_begin = chain_one.begin();//记得提前加上typename来表示后面的是一个类型而不是一个变量
    typename chain<T>::iterator one_end = chain_one.end();
    typename chain<T>::iterator two_begin = chain_two.begin();
    typename chain<T>::iterator two_end = chain_two.end();

    for (int i = 0; i <= size_total; i++)
    {
        T cur;
        //cout<<"i: "<<i<<endl;
        if (one_begin == one_end && two_begin == two_end)
        {
            final_answer[top] = answer;
            top++;
            return;
        }

        if (one_begin != one_end && two_begin != two_end)
        {
            if (*one_begin <= *two_begin)
            {
                cur = *one_begin;
                ++one_begin;
            }
            else {
                cur = *two_begin;
                ++two_begin;
            }
            answer += i ^ cur;
            answer_head.insert(i, cur);
            continue;
        }
        else if (one_begin != one_end && two_begin == two_end) {
            cur = *one_begin;
            ++one_begin;
            answer += i ^ cur;
            answer_head.insert(i, cur);
            continue;
        }
        else if (one_begin == one_end && two_begin != two_end) {
            cur = *two_begin;
            ++two_begin;
            answer += i ^ cur;
            answer_head.insert(i, cur);
            continue;
        }
    }
    //cout<<"end"<<endl;
    return;
}

int main()
{
    int N = 0, M = 0;
    chain<long> one;
    chain<long> two;
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        long val;
        cin >> val;
        one.insert(i, val);
    }
    for (int i = 0; i < M; i++)
    {
        long val;
        cin >> val;
        two.insert(i, val);
    }
    merge_chain<long> merge; 
    merge.merge_two(one, two, 10, 20);
    ///cout<<top<<endl;
    for (int i = 0; i < top; i++)
    {
        cout << final_answer[i] <<endl;
    }
    return 0;
}