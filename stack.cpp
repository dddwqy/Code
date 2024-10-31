#include<iostream>
#include<iomanip>
#include<algorithm>
#include<string>
using namespace std;

template<class T>
class stack
{
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T& thelement) = 0;
};

template<class T>
class arraystack :public stack<T>
{
public:
    arraystack(int inticapitity = 10)
    {
        arraylength = inticapitity;
        stacktop = -1;
        stack = new T[arraylength]();
    }
    ~arraystack()
    {
        delete[] stack;
    }

    bool empty() override
    {
        return stacktop == -1;
    }

    int size() override
    {
        return stacktop + 1;
    }

    T& top() override
    {
        if (!empty())
        {
            return stack[stacktop];
        }
        //cout<<"out of range"<<endl;
        throw out_of_range("out of range");
    }

    void pop() override
    {
        if (!empty())//不为空的话可以输出一些值
        {
            stack[stacktop].~T();
            stacktop--;
        }
        return;
    }

    void push(const T& thelement) override
    {
        if (stacktop == arraylength - 1)//表示这个stack满了
        {
            changelength();
        }
        stack[++stacktop] = thelement;
        return;
    }
private:
    void changelength();
    int stacktop;
    int arraylength;
    T* stack;
};
template<class T>
void arraystack<T>::changelength()
{
    T* newstack = new T[arraylength * 2]();
    copy(stack, stack + arraylength, newstack);//将原本的元数复制到新的数组中
    delete[] stack;
    stack = newstack;
    arraylength *= 2;
    return;
}

arraystack<double> num(1000);
arraystack<char> sign(1000);
double answer[1000] = { 0 };
int top=0;

void total();
void cul(arraystack<double>&num,arraystack<char>&sign);
void cul_before(arraystack<double>&num,arraystack<char>&sign);
double cul_kuohao(int&index, string& input);

int main()
{
    total();
    for (int i = 0; i < top; i++)
    {
        cout <<std::fixed<<std::setprecision(2)<< answer[i] << endl;
    }
    return 0;
}

void total()
{
    int j = 1;
    cin >> j;
    cin.ignore();//清除空格
    int count = 0;
    string input;
    while (count < j)
    {
        getline(cin, input);
        int i=0;
        for (i = 0; i < input.length(); i++)
        {
            char temp = input[i];
            if (temp >= '0' && temp <= '9'||temp==')')
            {
                //当输入为+-的时候不计算
                //当输入为*/的时候可以进行计算值
                if(temp!=')')
                {
                    num.push(static_cast<double>(temp - '0'));
                }
                if (!sign.empty() && (sign.top() == '*' || sign.top() == '/'))
                {
                    cul(num,sign);
                }
                if (i==input.length()-1)
                {
                   
                    cul_before(num,sign);
                }
            }
            else if (temp == '(')//当为（时先计算括号中的表达式
            {
                double tns=cul_kuohao(i,input);
                num.push(tns);
            }
            else {
                sign.push(temp);
            }
        }
        count++;
        answer[top++] = num.top();
    }
    return;
}

void cul(arraystack<double>&num,arraystack<char>&sign)
{
    double right = num.top();
    num.pop();
    double left = num.top();
    num.pop();
    char fuhao = sign.top();
    sign.pop();

    if (fuhao == '*')
    {
        num.push(left * right);
    }
    else {
        num.push(left / right);
    }
    return;
}

void cul_before(arraystack<double>&num,arraystack<char>&sign)//在计算完这个惩处值之后，要计算之前的其他的+-的值
{
    while (!sign.empty() && !num.empty())
    {
        double right = num.top();
        num.pop();
        double left = num.top();
        num.pop();
        char fuhao = sign.top();
        sign.pop();
        char sign_fuhao;
        if(!sign.empty())
        {
          sign_fuhao=sign.top();
          if(sign_fuhao=='-')
          {
             left=-1*left;
          }
          sign.pop();
          sign.push('+');
        }
        
        if (fuhao == '+')
        {
            num.push(right + left);
        }
        else {
            num.push(left - right);
        }
    }
    return;
}

//计算括号中的表达式是一个递归的过程，当在括号中的表达式再遇到了一个括号，递归调用这个函数
double cul_kuohao(int&index, string& input)
{   
    arraystack<double>num(100);
    arraystack<char>sign(100);
    for (index=index+1; index < input.length(); index++)
    {
       // cout<<input.length()<<endl;
        char temp = input[index];
        //cout<<temp<<' ';
        if (temp >= '0' && temp <= '9'||temp==')')
        {
            if(temp!=')')
            {
               num.push(static_cast<double>(temp - '0'));
            }
           
            if (!sign.empty() && (sign.top() == '*' || sign.top() == '/'))
            {
                cul(num,sign);
            }
            if (input[index+1]==')')//括号结束时计算当前栈中的表达式的值，并将结果返回上一层的表达式中，而不是在达到最后时计算
            {
                cul_before(num,sign);
                return num.top();
            }
        }
        else if (temp == '(')
        {
          double tns=cul_kuohao(index,input);
          num.push(tns);
        }
        else {
            sign.push(temp);
        }
    }
}