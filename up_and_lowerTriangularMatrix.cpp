#include<iostream>
using namespace std;

class lowerTriangularMatrix//下山脚
{
public:
  lowerTriangularMatrix(int m_n):n(m_n){element=new int[m_n*(m_n-1)/2]();}
  ~lowerTriangularMatrix()
  {
    delete []element;
  }
  void set(int i,int j,int newvalue);

  int n;//表示行数
  int size;//表示元素的个数
  int*element;//表示元素
};

void lowerTriangularMatrix::set(int i,int j,int newvalue)//
{
  if(i<1||j<1||i>n||j>n)
  {
      cout<<"error"<<endl;
  }else{
    if(i>=j)//处于下山脚的位置
    {
       element[i*(i-1)/2+j-1]=newvalue;
       size++;
    }
  }
}

class upTriangularMatrix//上山叫
{
public:
   upTriangularMatrix(int m_n):n(m_n){element=new int[m_n*(m_n-1)/2]();}
  ~upTriangularMatrix()
  {
    delete []element;
  }
  void set(int i,int j,int newvalue);

  int n;//表示行数
  int size;
  int*element;//表示元素
};

void upTriangularMatrix::set(int i,int j,int newvalue)
{
   if(i<1||j<1||i>n||j>n)
   {
     cout<<"error"<<endl;
   }else{
     if(i<=j)//处于上三角位置
     {
       element[n*(n+1)/2-i*(i+1)/2+j-i]=newvalue;
       size++;
     }
   }
}

int**answer;
int n;
int main()
{
    //int n;
    cin>>n;
    lowerTriangularMatrix test1(n);
    upTriangularMatrix test2(n);
    
    answer=new int*[n+1]();
    for(int i=1;i<=n;i++)
    {
       answer[i]=new int[n+1]();//分配一个二维数组的结果矩阵
    }

    return 0;
}

void mul(const lowerTriangularMatrix& test1,const upTriangularMatrix& test2)//实现两个三角矩阵的相乘
{
    int num_test2=n;
    int*start_test1=new int[n+1]();
    int*start_test2=new int[n+1]();//用于储存test2的每一行元素的起始位置
    for(int i=2;i<=n;i++)
    {
       start_test2[i]=start_test2[i-1]+num_test2;
       num_test2--;
    }
    for(int i=2;i<=n;i++)
    {
      start_test1[i]=start_test1[i-1]+(i-1);//用于表示test1的每一行的起始元素的索引
    }

    for(int row=1;row<=n;row++)//遍历结果矩阵的每一行
    {
      for(int j=start_test1[row];j<start_test1[row]+row;j++)//每一行的每一个元素,因为是下三角，所以第几行就有几个元素
      {
        for(int i=0;i<(n-()))
        {

        }
      }
    }


   
    return;
}
