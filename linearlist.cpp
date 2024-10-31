#include<iostream>
#include<string>
using namespace std;

int answer[2000];
int top;

struct person//实现一个人的信息
{
    string name;
    string phonenumber;
    int cla;
    int home;
    bool operator==(const person& temp)
    {
        if (name == temp.name && phonenumber == temp.phonenumber && cla == temp.cla && home == temp.home)
        {
            return true;
        }
        return false;
    }
};

//这是一个线性表的抽象类
template <class T>
class linearList
{
protected:
    
    virtual bool empty()=0;
    virtual int size()=0;
    virtual T& get(string index)=0;
    virtual int indexof(const T& temp)=0;
    virtual void erase(string index)=0;
    virtual void insert(const T& temp)=0;
    virtual void output()=0;
};

//实现一个通讯录，使用线性表来实现
template<class T>
class ContactList :public linearList<T>
{
public:
    ContactList(int m_contactlength = 1000);
    ~ContactList();
    void operation(int i);
protected:
    bool empty() override { return linearlength == 0; }
    int size() override { return linearlength; } 
    T& get(string index) override;
    int indexof(const T& temp) override;
    void erase(string index) override;
    void insert(const T& temp) override;
    void output() override;

private:
    void update(int xuhao, string& name);//用于编辑的函数
    void copy_forward(int index);//删除时将数组往前移动
    bool checkofindex(string m_name);
    void changelength(int newlength);//当需要改变长度时对数组进行扩容和减容
    person* member;
    int linearlength;//表示线性表的长度，就是数组中已经利用的长度
    int contactlength;//表示当前这个数组的总开辟长度
};
template<class T>
ContactList<T>::ContactList(int m_contactlength) :contactlength(m_contactlength)
{
    member = new T[contactlength]();//构造数组
    linearlength = 0;
}
template<class T>
ContactList<T>::~ContactList()
{
    delete[] member;//删掉数组
}
template<class T>
bool ContactList<T>::checkofindex(string m_name)//检查每个索引在不在范围内
{
    for (int i = 0; i < linearlength; i++)
    {
        if (member[i].name == m_name)
        {
            return true;
        }
    }
    return false;
}
template<class T>
T& ContactList<T>::get(string index)
{
    if (checkofindex(index))
    {
        for (int i = 0; i < linearlength; i++)
        {
            if (member[i].name == index)
            {
                return member[i];
            }
        }
    }
    throw std::out_of_range("name ont found");
}
template<class T>
void ContactList<T>::changelength(int newlength)
{
    if (newlength > 0)//保证新的长度是不小于0
    {
        T* temp = new T[newlength];
        int size = min(linearlength, newlength);
        for (int i = 0; i < size; i++)//拷贝数据
        {
            temp[i] = member[i];
        }
        delete[]member;
        member = temp;
    }
    return;
}
template<class T>
void ContactList<T>::insert(const T& temp)
{
    if (linearlength == contactlength)//判断数组是不是已经满了
    {
        changelength(2 * contactlength);
    }
    member[linearlength] = temp;
    //更新线性表长度和数组长度
    linearlength++;
    contactlength = contactlength * 2;
    return;
}
template<class T>
void ContactList<T>::erase(string index)
{
    if (checkofindex(index))
    {
        for (int i = 0; i < linearlength; i++)
        {
            if (member[i].name == index)
            {
                copy_forward(i);
                linearlength--;
                return;
            }
        }

    }
    return;
}
template<class T>
void ContactList<T>::copy_forward(int index)
{
    for (int i = index + 1; i < linearlength; i++)
    {
        member[i - 1] = member[i];
    }
    return;
}
template<class T>
int ContactList<T>::indexof(const T& temp)
{
    for (int i = 0; i < linearlength; i++)
    {
        if (member[i] == temp)
        {
            return i;
        }
    }
    return -1;//没找到从这里退出，返回-1表示没找到
}
template<class T>
void ContactList<T>::output()
{
    int cla;
    cin >> cla;

    int x = 0;
    for (int i = 0; i < linearlength; i++)
    {
        if (member[i].cla == cla)
        {
           x ^= member[i].home;
        }
    }
    answer[top] = x;
    top++;
    return;
}
template<class T>
void ContactList<T>::update(int xuhao, string& name)
{
    for (int i = 0; i < linearlength; i++)
    {
        if (member[i].name == name)
        {
            if (xuhao == 1)
            {
                string phone;
                cin >> phone;
                member[i].phonenumber = phone;
            }
            else if (xuhao == 2)
            {
                int cla;
                cin >> cla;
                member[i].cla = cla;
            }
            else if (xuhao == 3)
            {
                int home;
                cin >> home;
                member[i].home = home;
            }
            return;
        }
    }
    return;
}
template<class T>
void  ContactList<T>::operation(int i)
{
    if (i == 0)//插入
    {
        string name;
        int cla;
        string phonenumber;
        int home;
        cin >> name >> phonenumber >> cla >> home;
         T temp = { name,phonenumber,cla,home };
        insert(temp);

    }
    else if (i == 1)//删除
    {
        string name;
        cin >> name;
        erase(name);
    }
    else if (i == 2)//编辑
    {
        string name;
        int xuhao;
        cin >> name >> xuhao;
        update(xuhao, name);
    }
    else if (i == 3)//查找
    {
        string name;
        cin >> name;
        for (int i = 0; i < linearlength; i++)
        {
            if (member[i].name == name)
            {
                answer[top] = 1;
                top++;
                return;
            }
        }
        
        answer[top] = 0;
        top++;
    }
    else if (i == 4)//输出异或值
    {
        output();
    }
    return;
}

int main()
{
    ContactList<person> one(2000);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int j;
        cin >> j;
        one.operation(j);
    }
    for (int i=0;i<top;i++)
    {
        cout<<answer[i]<<endl;
    }
    return 0;
}