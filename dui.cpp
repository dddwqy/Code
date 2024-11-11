#include<iostream>
using namespace std;

int answer[100000];
int cnt;
class minheap//小根堆
{
public:
  minheap(int msize=5002)
  {
    arraylength=msize;
    heapsize=0;
    heap=new int[arraylength+1]();//从第一个位置开始
  }
  ~minheap(){delete [] heap;}
  bool empty(){return heapsize==0;}
  int size(){return heapsize;}
  int top()
  {
    if(heapsize==0)
    {
       cout<<"堆为空"<<endl;
    }
    return heap[1];
  }
  //int getheapsize(){return heapsize;};
  void pop();
  void sort(minheap*temp);
  void push(int temp);
  void initialize(int*new_array,int size);//初始化函数
  void output();
  void operation(int i)
  {
      if(i==1)
      {
        int temp;
        cin>>temp;
         //initialize();
        push(temp);
        answer[cnt]=heap[1];
        cnt++;
      }else if(i==2)
      {
        pop();
        answer[cnt]=heap[1];
        cnt++;
      }else if(i==3)
      {
        int n;
        cin>>n;
        minheap*temp=new minheap(6000);
        int* new_array=new int[6000+1]();    
        for(int i=1;i<=n;i++)
        {
          cin>>new_array[i];
        }
        temp->initialize(new_array,n);
       // temp->output();
        sort(temp);
        for(int i=0;i<cnt;i++)
        {
           cout<<answer[i]<<endl;
        }
        temp->output();
      }
  }
private:
  void changelength();
  int heapsize;
  int arraylength;
  int*heap;
};

void minheap::initialize(int*new_array,int size)
{
    delete [] heap;
    heap=new_array;
    new_array=nullptr;
    heapsize=size;
    //cout<<"enter end"<<endl;
    for(int i=heapsize/2;i>=1;i--)
    {
        //cout<<"enter for()"<<endl;
        int element=heap[i];
        int child=i*2;

        while(child<=heapsize)
        {
            //cout<<"enter while()"<<endl;
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
        //cout<<"end while()"<<endl;
    }
    //cout<<"end for()"<<endl;
    return;
}

void minheap::pop()
{
    if(heapsize==0)
    {
      cout<<"堆为空"<<endl;
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

void minheap::push(int temp)
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
    heap[currentnode]=temp;
    return;
}

void minheap::changelength()
{
    int*new_array=new int[arraylength*2]();
    for(int i=1;i<=arraylength;i++)
    {
      new_array[i]=heap[i];
    }
    delete [] heap;
    heap=new_array;
    new_array=nullptr;
    arraylength*=2;
    return;
}
void minheap::output()
{ 
    for(int i=heapsize;i>=1;i--)
    {
       cout<<heap[i]<<' ';
    }
    cout<<endl;
    return;
}

void minheap::sort(minheap*temp)
{
   int temp_heapsize=temp->heapsize;
   for(int i=temp->size()-1;i>=1;i--)
   {
     int x=temp->top();
     temp->pop();
     temp->heap[i+1]=x;
   }
   temp->heapsize=temp_heapsize;
   //temp->output();
   return;
}

int main()
{
    int n,m;
    //cin>>n;
    minheap test(6000);
    cin>>n;
    int* new_array=new int[6000+1]();    
    for(int i=1;i<=n;i++)
    {
        cin>>new_array[i];
    }
    test.initialize(new_array,n);
    answer[cnt]=test.top();
    cnt++;

    cin>>m;
    int op;
    for(int i=1;i<=m;i++)
    {
       cin>>op;
       test.operation(op);
    }
    return 0;
}
