#include<iostream>
using namespace std;


int answer[100000]={0};
int cnt;
class minheap//小根堆
{
public:
  minheap(int msize=10)
  {
    arraylength=msize;
    heapsize=0;
    heap=new int[arraylength+1]();//从第一个位置开始
  }
  ~minheap(){delete [] minheap;}
  bool empty(){return heapsize==0;}
  int size(){return heapsize;}
  int top()
  {
    if(heapsize==0)
    {
       return queueEmpty();
    }
    return heap[1];
  }
  void pop();
  void push(int temp);
  void initialize();//初始化函数
  int operation(int i)
  {
      if(i==1)
      {
        int temp;
        cin>>temp
         //initialize();
        push(temp);
        answer[cnt++]=heap[1];
      }else if(i==2)
      {
        pop();
        answer[cnt++]=heap[1];
      }
  }
private:
  void changelength();
  int heapsize;
  int arraylength;
  int*heap;
};

void initialize()
{
    for(int i=1;i<=heapsize;i++)
    {
       cin>>heap[i];
    }

    for(int i=heapsize/2;i>=1;i--)
    {
        int element=heap[i];
        int child=i*2;

        while(child<=heapsize)
        {
           if(child<heapsize&&heap[child+1]<heap[child])
           {
              child++;
           }
           if(element<heap[child])
           {
             break;
           }
           heap[child/2]=heap[child];
           child*=2;
        }
        heap[child/2]=element;
    }

    return;
}

void pop()
{
    if(heapsize==0)
    {
      return queueEmpty();
    }

    int lastelement=heap[heapsize--];
    int currentnode=1;
    int child=2;

    while(child<=heapsize)
    {
       if(child<heapsize&&heap[child]>heap[child+1])
       {
         child++;
       }
       if(lastelement<heap[child])
       {
         break;
       }
       heap[currentnode]=heap[child];
       currentnode=child;
       child*=2;
    }
    heap[currentnode]=lastelement;
    return;
}

void push(int temp)
{
    if(heapsize==arraylength-1)
    {
       changelength();
    }
    int currentnode=++heapsize;

    while(currentnode!=1&&temp<heap[currentnode/2])//当元素小于自己的父节点的时候我们就将元素上移动
    {
      heap[currentnode]=heap[currentnode/2];
      currentnode=currentnode/2;
    }
    heap[current]=temp;
    return;
}

void changelength()
{
    int new_array=new int[arraylength*2]();
    for(int i=1;i<=arraylength;i++)
    {
      new_array[i]=heap[i];
    }
    delete [] heap;
    heap=new_array;
    new_array=nullptr;
    arraylenth*=2;
    return;
}

int main()
{
    int n,m;
    cin>>n;
    minheap test(n);
    test.initialize();
    cin>>m;
    for(int i=1;i<=m;i++)
    {
       int op;
       cin>>op;
       test.operation(op);
    }


    return 0;
}